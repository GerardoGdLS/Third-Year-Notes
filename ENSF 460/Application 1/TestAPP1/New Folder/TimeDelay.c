#include "xc.h"
#include "TimeDelay.h"

void delay_ms(uint16_t time_ms)
{
    T2CONbits.TSIDL = 0;
    T2CONbits.T32 = 0;
    T2CONbits.TCS = 0;

    IPC1bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    T2CONbits.TCKPS = 0b10;
    // Adjust PR2 for 8 MHz clock
    PR2 = time_ms * 63; // Multiplied by 64 instead of 16 for 8 MHz clock
    TMR2 = 0;
    T2CONbits.TON = 1;
    
    Idle(); 
   
   
}

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;
    
     T2CONbits.TON = 0;
}