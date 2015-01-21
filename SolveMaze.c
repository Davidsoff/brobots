#include "simpletools.h"                      // Include simple tools
#include "servo.h"
#include "ping.h"
#include "abdrive.h"

volatile static int distance[2];
volatile static int state;
volatile static int left_turn_count;
unsigned int scannerStack[40+25];
unsigned int stateStack[40+25];

const int FRONT = 0;
const int RIGHT = 1;

void updateDistanceCog();
void driveStateCog();
void drive();
void escape();
void stop();
void turn_right();
void turn_left(int iter);

int main(){
  //initialisation
  int mode = 0;
  state = 0;
  left_turn_count = 0;
  cogstart(&updateDistanceCog, NULL, scannerStack, sizeof(scannerStack));
  cogstart(&driveStateCog, NULL, stateStack, sizeof(stateStack));
 
  //main program loop
  while(1){
    print("front : %d\n", distance[FRONT]);
    print("right : %d\n", distance[RIGHT]);
    print("state : %d\n", state);
    int right = distance[RIGHT];
    int front = distance[FRONT];
    int bumper = input(6);
    if(bumper == 0){
      state = 4;
    }
    else
    {      

      if(front>5){
        state = 1;
      
      //Rechts grote afstand, er kan een bocht worden gemaakt, deze functie wordt aangeroepen
      }else if(right > 15){
        state = 2;     
      }else{
        if(front <= 4){
          if(right <=15){
            state = 3;
          }
        }
      }
      if(front <= 2){
          state = -1;    
      }
    }   
  }  
  return 0; 
}  

void updateDistanceCog(){
  while(1){
    distance[FRONT] = ping_cm(2);
    pause(5);
    distance[RIGHT] = ping_cm(16);
    pause(5);
    
  }  
}  

void driveStateCog(){
  while(1){
    switch(state){
      case -2:
        while(input(6)==1{
          drive_speed(40,40);
        }
                  
      
      case -1:
        left_turn_count = 0;
        escape();
        state = 0;
      break;
      case 0:
        stop();
      break;
      case 1:
        left_turn_count = 0;
        drive();
      break;
      case 2:
        left_turn_count = 0;
        turn_right();
        state = 0;
      break;
      case 3:
        turn_left(left_turn_count++);
        state = 0;
      break;
      case 4:
        escape_bumper();
        state = 0;
      default:
        left_turn_count = 0;
        state = 0;
      break;
    }
    
  }  
}  

//robot rijd naar voren
void drive(){
  drive_speed(20, 20);
}

void escape(){
  high(26);
  drive_goto(-5,-5);
  low(26);
}

void stop(){
  drive_speed(0,0);
}

void escape_bumper(){
  escape();
  drive_goto(-6, 6); 
}  

//robot draait 90 graden naar rechts          
void turn_right(){
  drive_goto(12, 12);
  drive_goto(26, -25);
  drive_goto(50, 50);
}

//robot draait 90 graden naar links
void turn_left(int iter){
  if(iter == 0)
    drive_goto(-5, -5);
  drive_goto(-26, 25);
}    