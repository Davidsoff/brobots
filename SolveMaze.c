#include "simpletools.h"                      // Include simple tools
#include "servo.h"
#include "ping.h"
#include "abdrive.h"



//PARAMETERS

const int rightPingPort = 16;
const int frontPingPort = 2;
const int bumperPort = 6;

const int maxRightTurns = 5;
const int resetRightTurnsOnState1 = 0;




volatile static int distance[2];
volatile static int state;
volatile static int escapeCount;
volatile static int leftTurnCount;
volatile static int  rightTurnCount;
unsigned int scannerStack[40+25];
unsigned int stateStack[40+25];

const int FRONT = 0;
const int RIGHT = 1;

void updateDistanceCog();
void driveStateCog();
void drive();
void escape();
void stop();
void turnRight();
void rotateRight();
void turnLeft(int iter);
void startup();
void escapeBumper();

int main(){
  //initialisation
  state = -2;
  leftTurnCount = 0;
  rightTurnCount = 0;
  escapeCount = 0;
  
  //Start cogs
  cogstart(&updateDistanceCog, NULL, scannerStack, sizeof(scannerStack));
  cogstart(&driveStateCog, NULL, stateStack, sizeof(stateStack));
  pause(2000);
 
 
/*
 *MAIN PROGRAM LOOP
 */
  while(1){
    pause(100);
    int right = distance[RIGHT];
    int front = distance[FRONT];
    
    int bumper = input(bumperPort);
    
    
    if(bumper == 0){
      state = 4;  //Bumper is pressed
    }
    
    else if((right > 15)&&(right < 200)){
      state = 2; //Right turn 
    }
    
    else if(right < 10 && front <=  6){
      state = 3; //Left turn
    }
    
    else if(front>6){
      state = 1; //Drive forward
    }
    
    else{
      state = -1; 
    }   
  }  
  return 0; 
}  

/*
 *COG: PINGSENSORLOOP
 */
void updateDistanceCog(){
  while(1){
    distance[FRONT] = ping_cm(frontPingPort);
    pause(6);
    distance[RIGHT] = ping_cm(rightPingPort);
    pause(6);
    
  }  
}  

/*
 *COG: DRIVESTATECOG
 */
void driveStateCog(){
  while(1){
    switch(state){
      case -2:
        
        startup();
        leftTurnCount=0;
        rightTurnCount=0;
       break;
                  
      
      case -1:
        escapeCount++;
        leftTurnCount = 0;
        if(escapeCount<4){
          escape();
        }else{
          high(27);
          escapeCount = 0;
          pause(10);
          drive_goto(1, 1);
          drive_goto(-1, -1);
          rotateRight(); 
          low(27);
        }                  
        state = 0;
      break;
      
      case 0:
        stop();
      break;
      
      case 1:
        //drive forward
        leftTurnCount = 0;
        if(resetRightTurnsOnState1==1){
          rightTurnCount=0;
        }
        
        drive();
      break;
      
      
      case 2:
        //Turn right
        leftTurnCount = 0;
        turnRight();
        rightTurnCount++;
        state = 0;
      break;
      
      case 3:
        turnLeft(leftTurnCount++);
        rightTurnCount=0;
        state = 0;
      break;
      
      case 4:
        escapeBumper();
        state = 0;
      break;
      
      default:
        leftTurnCount = 0;
        state = 0;
      break;
    }
    
  }  
}  

//robot drives forward
void drive(){
  drive_speed(30, 30);
}

//robot drives a bit backwards
void escape(){
  high(26);//status led
  drive_goto(-5,-5);
  low(26);
}

void stop(){
  drive_speed(0,0);
}

//bumper is pressed
void escapeBumper(){
  escape();
  drive_goto(-3, 3); 
}  

//robot turns 90 degrees to the right          
     
void turnRight(){
  if((maxRightTurns>0)&&(rightTurnCount>maxRightTurns)){
    startup();
    return;
  }    
  drive_goto(12, 12);
  rotateRight();
}

void rotateRight(){
  drive_goto(26, -25);
  drive_goto(50, 50);
}  

//robot turns 90 degrees to the left
void turnLeft(int iter){
  if(iter == 0)
    drive_goto(-5, -5);
  drive_goto(-26, 25);
}    

void startup(){
  while(input(6)==1){
    drive_speed(40,40);
  }
  turnLeft(0);
}  