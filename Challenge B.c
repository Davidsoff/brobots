
#include "simpletools.h"                      
#include "servo.h"
#include "ping.h"
#include "abdrive.h"

//PARAMETERS
const int SWITCHPORT = 0;
const int PINGPORT = 3;
const int SERVOPORT = 17;
const int SERVOSPEED = 25;
const int SERVOTIME = 1000;
const int FWSPEED = 10;
const int BWSPEED = -10;
const int COMPDISTANCE = 20;//distance to comensate for the location of the pingsensor
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
  maxDistance = ping_cm(PINGPORT);//measure the distance between the ping sensor and the ground
  
  forwards();//Robot drives till its over the ledge
  
  turnServo();//Servo turns so the switch is downwards
  
  backwards();//Robot drives back till the switch is pressed   
}

//FUNCTIONS
int pingDistance()
{
  int distance = ping_cm(PINGPORT);
  
  print("%c distance = %d%c cm", HOME, distance, CLREOL);
  
  return distance;  
}

int stopSwitch()
{
  return input(SWITCHPORT);        
}

void forwards()
{
  while(pingDistance()<=maxDistance)
  {
    drive_speed(FWSPEED,FWSPEED);
  }
  drive_speed(0,0);
  pause(1000);   
  drive_goto(COMPDISTANCE, COMPDISTANCE);       
}

void backwards()
{
  int switchstatus=stopSwitch();
  while(switchstatus==1) //switch is not pressed
  {
    drive_speed(BWSPEED,BWSPEED);
    switchstatus=stopSwitch();
  }
  drive_speed(0,0);          
}      

void turnServo()
{
  servo_speed(SERVOPORT, SERVOSPEED);
  pause(SERVOTIME);
  servo_speed(SERVOPORT, 0);
}  
