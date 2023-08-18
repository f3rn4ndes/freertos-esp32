#pragma once

// Includes
#include <Arduino.h>
// #include <esp_system.h>
// #include <time.h>
// #include <sys/time.h>
// #include "peripheral.h"
#include "verbose.h"

// Defines
#define CLOCK_TIMEOUT_COUNTER_RESET 0UL // Timeout Counter
#define CLOCK_VALUE_RESET 0UL           // Initial Clock Time

#define CLOCK_TIMER_CHANNELS 10

#define CLOCK_TIMER_DISABLED false
#define CLOCK_TIMER_ENABLED true

#define CLOCK_TIMER_RESET true

// External Objects
extern VerboseTask verbose;

    // Data Types - typedefs, structs, unions and/or enumerated
    typedef enum {
        ctTimer01 = 0,
        ctTimer02,
        ctTimer03,
        ctTimer04,
        ctTimer05,
        ctTimer06,
        ctTimer07,
        ctTimer08,
        ctTimer09,
        ctTimer10
    } ClockTimer_t;

typedef struct
{
    boolean synchronized;
    timeval current;
    unsigned long timeoutCounter;
} sysClock_t;

typedef struct
{
    uint32_t startTime;
    uint8_t enabled;
} sysTimer_t;

// Constants

// Public Functions
void sysClockSetup(void);

void sysClockTimerMSInit(void);
void sysClockTimerUSInit(void);

void sysClockTimerMSControl(uint8_t pChannel, boolean pStatus);
void sysClockTimerUSControl(uint8_t pChannel, boolean pStatus);

void sysClockTimerUSReset(uint8_t pChannel);
uint32_t sysClockTimerUSElapsed(uint8_t pTimer, uint8_t pReset);

void sysClockTimerMSReset(uint8_t pChannel);
uint32_t sysClockTimerMSElapsed(uint8_t pTimer, uint8_t pReset);

void sysClockTimerUSShowElapsed(uint8_t pTimer, uint8_t pReset);
void sysClockTimerMSShowElapse(uint8_t pTimer, uint8_t pReset);
