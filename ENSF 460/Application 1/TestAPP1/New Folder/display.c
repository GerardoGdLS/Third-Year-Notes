

#include "xc.h"
#include "UART2.h" 
#include "display.h"
#include <stdio.h>

#define CLEAR_SCREEN "\033[2J\033[H" //This display message clears the UART display
#define ALARM_MESSAGE "FIN 00m : 00s -- ALARM"
#define RESET_MESSAGE "CLR 00m : 00s"

// Function to initialize the display
void initializeDisplay(void) {
    InitUART2();  // Initialize UART2 for communication
}

// Function to clear the display
void clearDisplay(void) {
    Disp2String(CLEAR_SCREEN);
}

// Function to display timer count
void displayTimerCount(unsigned int minutes, unsigned int seconds, const char* prefix) {
    char timerString[20];
    snprintf(timerString, sizeof(timerString), "%s %02um : %02us", prefix, minutes, seconds);
    clearDisplay();
    Disp2String(timerString);
}

// Function to update the timer display with the current timer values
void updateTimerDisplay(unsigned int minutes, unsigned int seconds) {
    displayTimerCount(minutes, seconds, "CNT");
}

// Function to display the set time
void displaySetTime(unsigned int minutes, unsigned int seconds) {
    displayTimerCount(minutes, seconds, "SET");
}

// Function to display a message indicating the timer has been reset
void displayResetMessage(void) {
    clearDisplay();
    Disp2String(RESET_MESSAGE);
}

// Function to display an alarm message
void displayAlarm(void) {
    clearDisplay();
    Disp2String(ALARM_MESSAGE);
}