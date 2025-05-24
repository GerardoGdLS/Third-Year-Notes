
#include "xc.h"
#include "TimerOperation.h"
#include "display.h"
#include "TimeDelay.h"
#include "IOs.h"


#define TICK_DURATION 800
#define BUTTON_DEBOUNCE_MS 600
#define RESET_THRESHOLD_MS 2400
#define FAST_INCREMENT_THRESHOLD_MS 3500

// State variable
static struct TimerState timerState = {0, 0, 0, 0, 0, 1, 0, 1, 0, 0};

void incrementMinutes(void) {
    timerState.minutes = (timerState.minutes + 1) % 60;
}

void incrementSeconds(void) {
    timerState.pb2HoldTime += BUTTON_DEBOUNCE_MS;

    if (timerState.pb2HoldTime >= FAST_INCREMENT_THRESHOLD_MS) {
        timerState.fastIncrementMode = 1;
    } else {
        timerState.fastIncrementMode = 0;
    }

    if (timerState.fastIncrementMode) {
        timerState.seconds = (timerState.seconds + 5) % 60;
    } else {
        timerState.seconds = (timerState.seconds + 1) % 60;
    }
}

void stopTimer(void) {
    timerState.isRunning = 0;
    if (!timerState.isFinished) {
        LED_PIN = 0;
    }
}

void resetTimer(void) {
    timerState.minutes = 0;
    timerState.seconds = 0;
    timerState.justReset = 1;
    timerState.isFinished = 0;
    stopTimer();
    displayResetMessage();
}

void timerFinished(void) {
    stopTimer();
    timerState.isFinished = 1;
    displayAlarm();
    LED_PIN = 1;
}

void handlePB3Press(void) {
    if (timerState.pb3PrevState == 0) {
        delay_ms(TICK_DURATION);
        timerState.pb3PressDuration += TICK_DURATION;
        if (timerState.pb3PressDuration >= RESET_THRESHOLD_MS) {
            resetTimer();
            timerState.pb3PressDuration = 0;
        }
    }
}

struct TimerState* getTimerState(void) {
    return &timerState;
}