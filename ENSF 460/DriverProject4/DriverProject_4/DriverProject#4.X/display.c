#include "xc.h"
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "display.h"
#include "UART2.h"
#include "ADC.h"
#define FCY 16000000UL
#include <libpic30.h>

#define MAX_BAR_LENGTH 32  // Maximum number of stars to display
#define ADC_MAX_VALUE 1023 // 10-bit ADC maximum value

void clearLine(void) {
    // Send carriage return and clear line with spaces
    Disp2String("\r");
    for (int i = 0; i < 60; i++) {  // Clear entire line width
        XmitUART2(' ', 1);
    }
    Disp2String("\r");
}

void display(uint16_t ADC_value) {
    // Calculate number of stars based on ADC value
    int numStars = (ADC_value * MAX_BAR_LENGTH) / ADC_MAX_VALUE;

    // Clear the line first
    clearLine();

    // Display mode label
    Disp2String("Mode 1: ");

    // Display bar graph
    for (int i = 0; i < numStars; i++) {
        XmitUART2('*', 1);
    }

    // Ensure at least one star is displayed if the value is very low
    if (numStars == 0) {
        XmitUART2('*', 1);
    }

    // Add space after bar graph
    XmitUART2(' ', 1);

    // Display hex value with proper formatting
    char hexBuffer[10];
    sprintf(hexBuffer, "0x%03X", ADC_value);
    Disp2String(hexBuffer);

    // Add a small delay to reduce display jitter
    __delay_ms(50);  // Use the library function directly
}
