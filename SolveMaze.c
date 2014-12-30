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
void turn_right();
void turn_left();




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
    int right = distance[RIGHT];
    int front = distance[FRONT];

    //Rechts grote afstand, er kan een bocht worden gemaakt, deze functie wordt aangeroepen
    if(right > 15){
      state = 2;     
    }else{
      if(front <= 5){
        state = 1;
      }
    }
    if(front < 5 ){
        state = -1;    
    }
  }   
  return 0; 
}  



void updateDistanceCog(){
  while(1){
    distance[FRONT] = ping_cm(0);
    pause(5);
    distance[RIGHT] = ping_cm(16);
    pause(5);
    
  }  
}  


void driveStateCog(){
  while(1){
    switch(state){
      case -1:
        left_turn_count = 0;
        escape();
      break;
      case 0:
      break;
      case 1:
        left_turn_count = 0;
        drive();
      break;
      case 2:
        left_turn_count = 0;
        turn_right();
      break;
      case 3:
        left_turn_count++;
        turn_left();
      break;
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
  low(26);
}

void escape(){
  drive_goto(-5,-5);
}

//robot draait 90 graden naar rechts          
void turn_right(){
  drive_goto(-5, -5);
  drive_goto(26, -25);
  drive_goto(40, 40);
  state = 1;
}

//robot draait 90 graden naar links
void turn_left(){
  //iteration is de hoeveelste keer dat de functie is uit gevoerd.
  if(left_turn_count > 1){
    drive_goto(-10, -10);
  }
  drive_goto(-26, 25);
  state = 0;
}    