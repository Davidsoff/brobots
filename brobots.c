

#include "simpletools.h"                      // Include simple tools
#include "servo.h"
#include "ping.h"

void pingThread(void* par);

int checkFront();
int checkRight();

static volatile int sonicFront, sonicRight;    // Global vars for cogs to share
unsigned int stack[40 + 25];                  // Stack vars for other cog

int main()                                    // main function
{
    
    servo_start();
    // Launch adder function into another cog (processor).
    //cogstart(&ping, NULL, stack1, sizeof(stack1));
    print("hoi");
    // Watch what the other cog is doing to the value of n.
    cogstart(&pingThread, NULL, stack, sizeof(stack));
    while(1)
    {
        // Display result
        print("data: \n");
        pause(1000);
        print("Front %d\n", sonicFront);
        print("Right %d\n" , sonicRight );                              	// Wait 1/10 of a second
    }
}

// Function that can continue on its
// own if launched into another cog.
void pingThread(void* par)                         // adder keeps going on its own
{
    while(1)                                    // Endless loop
    {
        sonicFront = checkFront();
        pause(300);
        sonicRight = checkRight();
        pause(300);                              // Wait for t ms between updates
    }
}

int checkFront(){
    servo_angle(16, 2050);
    pause(500);
    return ping_cm(17);
}

int checkRight(){
    servo_angle(16, 1000);
    pause(500);
    return ping_cm(17);
}