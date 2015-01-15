
/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools

int main()                                    // Main function
{
  // Add startup code here.
  i2c *i2c_bus;
  
  i2c_bus = i2c_newbus(10, 11, 0);
 
  while(1)
  {
    // Add main loop code here.
    
  }  
}
