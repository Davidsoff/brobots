
#include "simpletools.h"                      
#include "servo.h"
#include "ping.h"
#include "abdrive.h"


//PARAMETERS
const int switchport = 0;
int pingport = 1;
int servoport = 16;
int servospeed = 25;
int servotime = 1000;
int fwspeed = 10;
int bwspeed = -10;
int compdistance = 20;//distance to comensate for the location of the pingsensor
int maxDistance = 10;//ping distance

//FUNCTION INITIALISATION
int pingDistance();
int stopSwitch();
void forwards();
void backwards();
void turnServo();



//MAIN FUNCTION
int main()                                  
{
  maxDistance = ping_cm(pingport);//measure the distance between the ping sensor and the ground
  
  forwards();//Robot drives till its over the ledge
  
  turnServo();//Servo turns so the switch is downwards
  
  backwards();//Robot drives back till the switch is pressed   
}


//FUNCTIONS
int pingDistance()
{
  int distance = ping_cm(pingport);
  
  print("%c distance = %d%c cm", HOME, distance, CLREOL);
  
  return distance;  
}



int stopSwitch()
{
  return input(switchport);        
}



void forwards()
{
  while(pingDistance()<=maxDistance)
  {
    drive_speed(fwspeed,fwspeed);
  }
  drive_speed(0,0);
  pause(1000);   
  drive_goto(compdistance, compdistance);       
}


void backwards()
{
  int switchstatus=stopSwitch();
  while(switchstatus==1) //switch is not pressed
  {
    drive_speed(bwspeed,bwspeed);
    switchstatus=stopSwitch();
  }
  drive_speed(0,0);          
}      



void turnServo()
{
  servo_speed(servoport, servospeed);
  pause(servotime);
  servo_speed(servoport, 0);
}



    
