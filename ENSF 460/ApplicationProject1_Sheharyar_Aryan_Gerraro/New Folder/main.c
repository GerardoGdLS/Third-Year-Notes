#include "xc.h"
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "IOs.h"
#include "clkChange.h"
#include "display.h"


// Configuration bits (unchanged)
#pragma config BWRP = OFF
#pragma config BSS = OFF
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config FNOSC = FRC
#pragma config IESO = OFF
#pragma config POSCMOD = NONE
#pragma config OSCIOFNC = ON
#pragma config POSCFREQ = HS
#pragma config SOSCSEL = SOSCHP
#pragma config FCKSM = CSECMD
#pragma config WDTPS = PS32768
#pragma config FWPSA = PR128
#pragma config WINDIS = OFF
#pragma config FWDTEN = OFF
#pragma config BOREN = BOR3
#pragma config PWRTEN = ON
#pragma config I2C1SEL = PRI
#pragma config BORV = V18
#pragma config MCLRE = ON
#pragma config ICS = PGx2
#pragma config DSWDTPS = DSWDTPSF
#pragma config DSWDTOSC = LPRC
#pragma config RTCOSC = SOSC
#pragma config DSBOREN = ON
#pragma config DSWDTEN = ON



// Function prototypes
void initializeSystem(void);
void configureClockOutput(void);

int main(void) {
    initializeSystem();
    
    while(1) {
        checkIO();
    }
    
    return 0;
}

void initializeSystem(void) {
    configureClockOutput();
    initializeIO();
    newClk(8); // Set to 8 MHz
    initializeDisplay();
}

void configureClockOutput(void) {
    TRISBbits.TRISB15 = 0;
    REFOCONbits.ROEN = 1;
    REFOCONbits.ROSSLP = 0;
    REFOCONbits.ROSEL = 0;
    REFOCONbits.RODIV = 0b0000;
}