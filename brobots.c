

#include "simpletools.h"                      // Include simple tools

void ping(void *par);
                       // Forward declaration

static volatile int sonicFront, sonicRight;    // Global vars for cogs to share
//unsigned int stack1[40 + 25];                  // Stack vars for other cog

int main()                                    // main function
{


  // Launch adder function into another cog (processor).
  //cogstart(&ping, NULL, stack1, sizeof(stack1));

  // Watch what the other cog is doing to the value of n.
  while(1)
  {
    servo_angle(16,1000);
    sonicRight = ping_cm(17);
    servo_angle(16,2050);
    sonicRight = ping_cm(17);

    print("front = %d cm\n", sonicFront);
    print("right = %d cm\n", sonicRight);                    // Display result
    pause(100);                               	// Wait 1/10 of a second
  }
}

// Function that can continue on its
// own if launched into another cog.
void ping(void *par)                         // adder keeps going on its own
{
  while(1)                                    // Endless loop
  {
    checkFront();
    pause(100);
    checkRight();                                // n + 1 each time loop repeats
    pause(100);                                 // Wait for t ms between updates
  }
}

void checkRight(){
  //turn servo to the right
  servo_angle(16,1000);
  sonicRight = ping_cm(17);
}
void checkFront(){
 //turn servo to front
  servo_angle(16,2050);
  sonicRight = ping_cm(17);
}

