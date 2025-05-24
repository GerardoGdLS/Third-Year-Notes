#ifndef DISPLAY_H
#define DISPLAY_H

// Function prototypes
void initializeDisplay(void);
void clearDisplay(void);
void displayTimerCount(unsigned int minutes, unsigned int seconds, const char* prefix);
void updateTimerDisplay(unsigned int minutes, unsigned int seconds);
void displaySetTime(unsigned int minutes, unsigned int seconds);
void displayResetMessage(void);
void displayAlarm(void);

#endif // DISPLAY_H