
#ifndef IOS_H
#define IOS_H

#include <xc.h>
#include <stdint.h>

// Function prototypes
void IOInit(void);
void IOCheck(void);
void controlLEDBrightness(void);
void TransmitDataToUART(void);
void Disp3Dec(uint16_t value);

#endif // IOS_H


