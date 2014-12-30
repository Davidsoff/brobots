#include "simpletools.h"                      // Include simple tools
#include "servo.h"
#include "ping.h"
#include "abdrive.h"

volatile static int distance[2];
unsigned int scannerStack[40+25];

const int FRONT = 0;
const int RIGHT = 1;

void updateDistanceCog();
void turn_right();
void turn_left(int);




int main(){
 int mode = 0;
 cogstart(&updateDistanceCog, NULL, scannerStack, sizeof(scannerStack));
 while(1){
   print("front : %d\n", distance[FRONT]);
   print("right : %d\n", distance[RIGHT]);
   pause(1000);
   if(distance[RIGHT] > 15){
    turn_right();
    drive_goto(40, 40);
   }     
   if(distance[RIGHT] >= 4 && distance[RIGHT] <= 5 && distance[FRONT] > 5){
     drive_speed(20, 20);
     low(26);
   }else{
     if(distance[FRONT] < 5){
      high(26);
      drive_speed(0, 0); 
     }       
     else
     {
      drive_speed(0, 0);
      high(25);
      if(distance[RIGHT] < 4){
         drive_goto(5, 20);
         drive_goto(17, 5);
         drive_goto(-10, -10);
       }        
      else if(distance[RIGHT] > 5 && distance[RIGHT] < 15){
          drive_goto(20, 5);
          drive_goto(5, 17);
          drive_goto(-10, -10);
       }//turn_right()        
       low(25);
     }     
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

//robot draait 90 graden naar rechts          
void turn_right(){
  drive_goto(-5, -5);
  drive_goto(26, -25);
}

//robot draait 90 graden naar links
void turn_left(int iteration){
  //iteration is de hoeveelste keer dat de functie is uit gevoerd.
  if(iteration > 0)
    drive_goto(-10, -10);
  drive_goto(-26, 25);
}    