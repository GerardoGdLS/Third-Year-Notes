

#ifndef TIMEROPERATION_H
#define TIMEROPERATION_H

struct TimerState {
    unsigned int minutes;
    unsigned int seconds;
    int isRunning;
    int justReset;
    int pb3PressDuration;
    int pb3PrevState;
    int pb2HoldTime;
    int pb2PrevState;
    int fastIncrementMode;
    int isFinished;
};

// Function prototypes
void initializeTimer(void);
void incrementMinutes(void);
void incrementSeconds(void);
void stopTimer(void);
void resetTimer(void);
void timerFinished(void);
void handlePB3Press(void);
struct TimerState* getTimerState(void);

#endif // TIMEROPERATION_H