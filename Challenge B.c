
#include "simpletools.h"                      
#include "servo.h"
#include "ping.h"
#include "abdrive.h"


//PARAMETERS
int switchport = 3;
int pingport = ;
int servoport = ;
int servospeed = 25;
int servotime = ;
int fwspeed = 10;
int bwspeed = -10;
int maxDistance = ;





int main()                                  
{
  forwards();//Robot drives till its over the ledge
  
  turnServo();//Servo turns so the switch is downwards
  
  backwards();//Robot drives back till the switch is pressed   
}



int pingDistance()
{
  int distance = ping_cm(pingport);
  
  print("%c distance = %d%c cm", HOME, distance, CLREOL);
  
  return distance;  
}



int stopHere()
{
  int switch = input(switchport);
  
  if(switch == 0)
  {
    return 0; //switch is pressed
  }
  else
  {
    return 1; //switch is not pressed
  }           
}



void forwards()
{
  while(pingDistance()<maxDistance)
  {
    drive_speed(fwspeed,fwspeed);
  }
  drive_speed(0,0);          
}


void backwards()
{
  while(stopHere()=1) //switch is not pressed
  {
    drive_speed(bwspeed,bwspeed);
  }
  drive_speed(0,0);          
}      



void turnServo()
{
  servo_speed(servoport, servospeed);
  wait(servotime);
  servo_speed(servoport, 0);
}



    