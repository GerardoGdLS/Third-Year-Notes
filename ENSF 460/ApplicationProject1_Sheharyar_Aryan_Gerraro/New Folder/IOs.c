#include "xc.h"
#include "TimeDelay.h"
#include "clkChange.h"
#include "UART2.h"
#include "display.h"
#include "TimerOperation.h"

// Constants (We added these to improve readability)
#define LED_PIN LATBbits.LATB8
#define PB1 PORTAbits.RA2
#define PB2 PORTAbits.RA4
#define PB3 PORTBbits.RB4
#define TICK_DURATION 968
#define BUTTON_DEBOUNCE_MS 600

void initializeIO(void) {
    AD1PCFG = 0xFFFF;
    
    CNPU1bits.CN0PUE = 1;
    CNPU1bits.CN1PUE = 1;
    CNPU2bits.CN30PUE = 1;
     
    CNEN1bits.CN0IE = 1;
    CNEN1bits.CN1IE = 1;
    CNEN2bits.CN30IE = 1;
    
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    
    TRISBbits.TRISB8 = 0;
    LED_PIN = 0;
    
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB4 = 1;
    
    initializeDisplay();
}

void checkIO(void) {
    struct TimerState* timerState = getTimerState();

    if (!timerState->isRunning && !timerState->isFinished && PB1 && PB2 && PB3) {
        if (!U2STAbits.TRMT) {
            Idle();
        }
    } else {
        handlePB3Press();

        if (!PB1 && !timerState->isRunning && !timerState->isFinished) {
            incrementMinutes();
            displaySetTime(timerState->minutes, timerState->seconds);
            delay_ms(BUTTON_DEBOUNCE_MS);
        }

        if (!PB2 && !timerState->isRunning && !timerState->isFinished) {
            incrementSeconds();
            displaySetTime(timerState->minutes, timerState->seconds);
            delay_ms(BUTTON_DEBOUNCE_MS);
        }

        if (timerState->isRunning) {
            LED_PIN ^= 1;
            if (timerState->seconds > 0) {
                timerState->seconds--;
            } else if (timerState->minutes > 0) {
                timerState->minutes--;
                timerState->seconds = 59;
            } else {
                timerFinished();
            }
            if (!timerState->isFinished) {
                updateTimerDisplay(timerState->minutes, timerState->seconds);
            }
            delay_ms(TICK_DURATION);
        } else if (timerState->isFinished) {
            LED_PIN = 1;
        } else {
            LED_PIN = 0;
        }
        
        timerState->pb2PrevState = PB2;
    }
}

void __attribute__((interrupt, auto_psv)) _CNInterrupt(void) {
    IFS1bits.CNIF = 0;

    struct TimerState* timerState = getTimerState();
    int pb3State = PB3;
    int pb2State = PB2;

    if (timerState->pb3PrevState == 1 && pb3State == 0) {
        timerState->pb3PressDuration = 0;
    }
    
    if (timerState->pb2PrevState == 1 && pb2State == 0) {
            timerState->pb2HoldTime = 0;
            timerState->fastIncrementMode = 0;
        }

    if (timerState->pb3PrevState == 0 && pb3State == 1) {
        if (timerState->justReset) {
            timerState->justReset = 0;
        } else if (timerState->isFinished) {
            timerState->minutes = 0;
            timerState->seconds = 0;
            timerState->justReset = 1;
            timerState->isFinished = 0;
            timerState->isRunning = 0;
            if (!timerState->isFinished) {
                LED_PIN = 0;
    }
        } else {
            if(timerState->isRunning){
                timerState->isRunning = 0;
                if (!timerState->isFinished) {
                    LED_PIN = 0;
                }
            } else{
                timerState->isRunning = 1;
                timerState->isFinished = 0;
            }
        }
    }

    timerState->pb3PrevState = pb3State;
    timerState->pb2PrevState = pb2State;
}