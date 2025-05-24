//filename: IOs.c
#include "xc.h"
#include "IOs.h"
#include "pwm.h" 
#include "ADC.h"
#include "UART2.h"
#include <p24F16KA101.h>
#define FCY 4000000UL
#include<libpic30.h>

// Define bounds for brightness
#define MAX_PWM 0xFFFF
#define MIN_PWM 0x0000

// Global variables to track button states and system modes
static int systemOn = 0;         // 0 for OFF, 1 for ON
static int ledBlinking = 0;      // 0 for not blinking, 1 for blinking
static int uartTransmitting = 0; // 0 for not transmitting, 1 for transmitting
static uint16_t currentBrightness = 0;
static uint16_t currentADCValue = 0;
static int ledOn = 0;

// Flags for button and timer interrupts
volatile int pb1_flag = 0;
volatile int pb2_flag = 0;
volatile int pb3_flag = 0;
volatile int timer1_flag = 0;

// **Add this line to declare adcReadFlag**
volatile int adcReadFlag = 0;
void IOInit() {
    // Configure pins
    TRISAbits.TRISA2 = 1; // PB1
    TRISAbits.TRISA4 = 1; // PB2
    TRISBbits.TRISB4 = 1; // PB3

    // Enable pull-up resistors
    CNPU1bits.CN0PUE = 1;  // RA4/CN0
    CNPU1bits.CN1PUE = 1;  // RB4/CN1
    CNPU2bits.CN30PUE = 1; // RA2/CN30

    // Enable Change Notification
    CNEN1bits.CN0IE = 1;   // RA4
    CNEN1bits.CN1IE = 1;   // RB4
    CNEN2bits.CN30IE = 1;  // RA2

    // Configure CN interrupts
    IPC4bits.CNIP = 7;     // Set CN interrupt priority
    IFS1bits.CNIF = 0;     // Clear CN interrupt flag
    IEC1bits.CNIE = 1;     // Enable CN interrupts

    // Initialize Timer1 for LED blinking
    T1CON = 0;               
    T1CONbits.TCKPS = 0b10;  // 1:64 prescaler
    PR1 = 31249;             // For 0.5 second intervals (assuming FCY = 4MHz)
    TMR1 = 0;                // Reset Timer1 counter
    IPC0bits.T1IP = 5;       
    IFS0bits.T1IF = 0;       
    IEC0bits.T1IE = 1;       

    // Initialize Timer 2 for periodic ADC readings
    T2CON = 0;                  // Clear Timer 2 configuration
    T2CONbits.TCKPS = 0b10;     // Set prescaler to 1:64
    PR2 = 6249;                 // Set period for 10 ms interval 
    TMR2 = 0;                   // Reset Timer 2 counter

    // Configure Timer 2 Interrupt
    IPC1bits.T2IP = 4;          // Set Timer 2 interrupt priority
    IFS0bits.T2IF = 0;          // Clear Timer 2 interrupt flag
    IEC0bits.T2IE = 1;          // Enable Timer 2 interrupt

    T2CONbits.TON = 1;          // Start Timer 2
    
    
    
    // Initialize other modules
    InitUART2();
    PWM_Init();

    // Configure ADC
    AD1PCFG = 0xFFFF;
}

void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0; // Clear CN interrupt flag
    // Set flags based on button release events
    if (!PORTAbits.RA2) pb1_flag = 1;
    if (!PORTAbits.RA4) pb2_flag = 1;
    if (!PORTBbits.RB4) pb3_flag = 1;
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    IFS0bits.T1IF = 0;  // Clear Timer1 interrupt flag
    timer1_flag = 1;    // Set flag to indicate Timer1 event
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;          // Clear Timer 2 interrupt flag
    adcReadFlag = 1;            // Set flag to indicate ADC should be read
}

void IOCheck() {
    // PB1: Toggle system state
    if (pb1_flag) {
        pb1_flag = 0;
        systemOn = !systemOn;
        if (!systemOn) {
            ledBlinking = 0;
            T1CONbits.TON = 0;  // Stop Timer1
            PWM_SetDutyCycle(MIN_PWM);
        } else {
            if (!ledBlinking) {
                controlLEDBrightness(); // Update brightness immediately
            }
        }
    }

    // PB2: Toggle LED blinking
    if (pb2_flag) {
        pb2_flag = 0;
        ledBlinking = !ledBlinking;
        if (ledBlinking) {
            T1CONbits.TON = 1;  // Start Timer1
            ledOn = 1;
        } else {
            T1CONbits.TON = 0;  // Stop Timer1
            if (systemOn) {
                controlLEDBrightness(); // Return to normal brightness control
            } else {
                PWM_SetDutyCycle(MIN_PWM);
            }
        }
    }

    // PB3: Toggle UART transmission
    if (pb3_flag) {
        pb3_flag = 0;
        uartTransmitting = !uartTransmitting;
        if (uartTransmitting) {
            TransmitDataToUART();
        }
    }

    // Handle Timer1 events for blinking
    if (timer1_flag) {
        timer1_flag = 0;

        ledOn = !ledOn;

        if (systemOn) {
            currentADCValue = readADC();
            currentBrightness = ((uint32_t)currentADCValue * MAX_PWM) / 0x03FF;
            PWM_SetDutyCycle(ledOn ? currentBrightness : MIN_PWM);
        } else {
            PWM_SetDutyCycle(ledOn ? MAX_PWM : MIN_PWM);
        }

        if (uartTransmitting) {
            TransmitDataToUART();
            __delay_ms(1);
            TransmitDataToUART();
        }
    }

    // Update brightness when adcReadFlag is set
    if (adcReadFlag) {
        adcReadFlag = 0;         // Clear the flag

        // Update brightness only when system is ON and not blinking
        if (systemOn && !ledBlinking) {
            controlLEDBrightness();
            if (uartTransmitting) {
                TransmitDataToUART();
            }
        }
      // Optionally handle UART transmission when system is OFF
        if (!systemOn && !ledBlinking) {
            if (uartTransmitting) {
                TransmitDataToUART();
            }
        }
    }
    // Small delay to allow interrupts to be serviced
    __delay_ms(1);
}


void controlLEDBrightness() {
    currentADCValue = readADC();
    currentBrightness = ((uint32_t)currentADCValue * MAX_PWM) / 0x03FF;
    PWM_SetDutyCycle(currentBrightness);
}

void TransmitDataToUART() {
    uint32_t intensity;

    if (ledBlinking) {
        if (systemOn) {
            // ON mode blinking
            intensity = ledOn ? ((uint32_t)currentBrightness * 100) / MAX_PWM : 0;
        } else {
            // OFF mode blinking - 100% or 0%
            intensity = ledOn ? 100 : 0;
        }
    } else {
        // Normal mode - show current intensity
        intensity = ((uint32_t)currentBrightness * 100) / MAX_PWM;
    }

    // Send intensity and ADC readings
    XmitUART2('\r', 1);
    XmitUART2('\n', 1);
    Disp3Dec((uint16_t)intensity);
    XmitUART2(',', 1);
    XmitUART2(' ', 1);

        Disp2Hex(currentADCValue);

}

void Disp3Dec(uint16_t value) {
    if (value >= 100) {
        XmitUART2((value / 100) % 10 + '0', 1);
        XmitUART2((value / 10) % 10 + '0', 1);
        XmitUART2(value % 10 + '0', 1);
    } else if (value >= 10) {
        XmitUART2((value / 10) % 10 + '0', 1);
        XmitUART2(value % 10 + '0', 1);
    } else {
        XmitUART2(value % 10 + '0', 1);
    }
}
