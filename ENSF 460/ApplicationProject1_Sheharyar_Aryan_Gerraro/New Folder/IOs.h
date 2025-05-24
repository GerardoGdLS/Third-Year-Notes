
#ifndef IOS_H
#define IOS_H

// Constants
#define LED_PIN LATBbits.LATB8
#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define TICK_DURATION 800
#define BUTTON_DEBOUNCE_MS 600

// Function prototypes
void initializeIO(void);
void checkIO(void);

#endif // IOS_H
