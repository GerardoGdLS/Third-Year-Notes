#ifndef IOS_H
#define IOS_H

#include <stdint.h>

// Define the modes
#define MODE0 0
#define MODE1 1

// Extern variables for button state and mode
extern volatile int buttonPressed;   // Declare buttonPressed as external
extern volatile int currentMode;     // Declare currentMode as external

// Function prototypes
void IOinit(void);
void Mode0(void);
void Mode1(void);

#endif // IOS_H
