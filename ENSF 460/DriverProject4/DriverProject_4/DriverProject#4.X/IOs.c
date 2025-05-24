

#include "IOs.h"
#include "clkChange.h"
#include "xc.h"
#include <p24F16KA101.h>
#include <stdio.h>
#include "UART2.h"
#include "ADC.h"
#include "display.h"

#define MODE0 0
#define MODE1 1
//
volatile int currentMode = MODE1;  // Start in Mode 1


void IOinit(void) {
    //AD1PCFG = 0xFFFF;  // Set all pins to digital mode
    
    // Configure  resistors
    CNPU1bits.CN0PUE = 1;  // Enables pull up resistor for PB3 
    CNPU1bits.CN1PUE = 1;  // Enables pull up resistor for PB2 
    CNPU2bits.CN30PUE = 1; // Enables pull up resistor forPB1 
     
    // Set up Change Notification (CN) interrupt for PB1
    TRISAbits.TRISA2 = 1;  // PB1 as input
    CNEN2bits.CN30IE = 1;   // Enable CN interrupt for PB1
    IEC1bits.CNIE = 1;     // Enable CN interrupts
    IFS1bits.CNIF = 0;     // Clear CN interrupt flag
    
    InitUART2();
}




void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0;  // Clear interrupt flag
    }

void Mode0(void) {
    // Transmit ADC value through UART for Python program
    uint16_t adcValue = do_ADC();
    char buffer[20];
    sprintf(buffer, "0x%03X\r\n", adcValue);
    Disp2String(buffer);  // Transmit ADC value via UART
}

void Mode1(void) {
    // Display ADC value as a bar graph on the terminal
    uint16_t adcValue = do_ADC();
    display(adcValue);  // Use existing display function
}