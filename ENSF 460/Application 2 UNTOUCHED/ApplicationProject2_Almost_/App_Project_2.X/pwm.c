
#include "xc.h"
#include "pwm.h"
#include <p24F16KA101.h>

// Constants for PWM configuration
#define MAX_PWM 0xFFFF
#define MIN_PWM 0x0000
#define PWM_MODE 0b110  // PWM mode without fault pin
#define TIMER3_SOURCE 1 // Use Timer 3 as the clock source

// Function to initialize the PWM module
void PWM_Init() {
    // Initialize the PWM period and duty cycle
    OC1R = MIN_PWM;   // Initial duty cycle (0%)
    OC1RS = MIN_PWM;  // Initialize secondary register
    
    // Configure Output Compare 1 (OC1)
    OC1CONbits.OCTSEL = TIMER3_SOURCE; // Select Timer 3 as the clock source
    OC1CONbits.OCM = PWM_MODE;         // Set PWM mode without fault pin

    // Start Timer 3
    T3CONbits.TON = 1;          // Enable Timer 3
}


// Function to set the PWM duty cycle
void PWM_SetDutyCycle(unsigned int duty) {
    if (duty <= MAX_PWM) {
        OC1RS = duty; // Set the duty cycle
    } else {
        OC1RS = MAX_PWM; // Clamp to maximum if out of range
    }
}
