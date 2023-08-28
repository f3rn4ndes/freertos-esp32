#include "sysclock.h"

sysTimer_t sysTimerUS[CLOCK_TIMER_CHANNELS];
sysTimer_t sysTimerMS[CLOCK_TIMER_CHANNELS];

// Functions

void sysClockSetup(void)
{
    sysClockTimerMSInit();
    sysClockTimerUSInit();
}

void sysClockTimerMSInit(void)
{
    for (int i = 0; i < CLOCK_TIMER_CHANNELS; i++)
    {
        sysTimerMS[i].enabled = CLOCK_TIMER_DISABLED;
        sysTimerMS[i].startTime = 0;
    }
}

void sysClockTimerUSInit(void)
{
    for (int i = 0; i < CLOCK_TIMER_CHANNELS; i++)
    {
        sysTimerUS[i].enabled = CLOCK_TIMER_DISABLED;
        sysTimerUS[i].startTime = 0;
    }
}

void sysClockTimerMSControl(uint8_t pChannel, boolean pStatus)
{
    sysTimerMS[pChannel].enabled = pStatus;
}

void sysClockTimerUSControl(uint8_t pChannel, boolean pStatus)
{
    sysTimerUS[pChannel].enabled = pStatus;
}

void sysClockTimerUSReset(uint8_t pChannel)
{
    if (pChannel >= CLOCK_TIMER_CHANNELS)
        pChannel = ctTimer10;

    sysTimerUS[pChannel].startTime = micros();
}

uint32_t sysClockTimerUSElapsed(uint8_t pChannel, uint8_t pReset)
{
    uint32_t _elapsed;

    if (pChannel >= CLOCK_TIMER_CHANNELS)
        pChannel = ctTimer10;

    _elapsed = micros() - sysTimerUS[pChannel].startTime;

    if (pReset)
        sysClockTimerUSReset(pChannel);

    return (_elapsed);
}

void sysClockTimerMSReset(uint8_t pChannel)
{
    if (pChannel >= CLOCK_TIMER_CHANNELS)
        pChannel = ctTimer10;
    sysTimerMS[pChannel].startTime = millis();
}

uint32_t sysClockTimerMSElapsed(uint8_t pChannel, uint8_t pReset)
{
    uint32_t _elapsed;

    _elapsed = millis() - sysTimerMS[pChannel].startTime;

    if (pReset)
        sysClockTimerMSReset(pChannel);

    return (_elapsed);
}

void sysClockTimerMSShowElapse(uint8_t pChannel, uint8_t pReset)
{
    if (pChannel >= CLOCK_TIMER_CHANNELS)
        pChannel = ctTimer10;
    if (sysTimerMS[pChannel].enabled)
        VERBOSE((String) "Timer (" + String(pChannel + 1) + ") Elapsed (ms): " + String(sysClockTimerMSElapsed(pChannel, pReset)), VERBOSE_MODULE_SYSCLOCK);
}

void sysClockTimerUSShowElapsed(uint8_t pChannel, uint8_t pReset)
{
    if (pChannel >= CLOCK_TIMER_CHANNELS)
        pChannel = ctTimer10;
    if (sysTimerUS[pChannel].enabled)
        VERBOSE((String) "Timer (" + String(pChannel + 1) + ") Elapsed (us): " + String(sysClockTimerUSElapsed(pChannel, pReset)), VERBOSE_MODULE_SYSCLOCK);
}
