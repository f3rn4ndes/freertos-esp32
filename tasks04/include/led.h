/*
  Copyright (c), 2023
  All rights reserved.
*/
#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtostasktemplate.h"
#include "systemtasks.h"
#include "board.h"

// Defines
#define LED_OFF 0
#define LED_ON 1
#define LED_F1 BOARD_LED_F1_PIN
#define LED_F2 BOARD_LED_F2_PIN

// Data Types - typedefs, structs, unions and/or enumerated
#define LEDMODE_MAX_ITENS 10

typedef enum
{
    lmClear = 0,
    lmSolid,
    lmSlowBlink,
    lmBlink,
    lmFastBlink,
    lmPulse,
    lmCustom
} LedStatus_t;

// led modes
typedef struct
{
    unsigned char state;
    unsigned int delay;
} LedMode_t;

const LedMode_t LED_MODES[][LEDMODE_MAX_ITENS] = {
    {
        {LED_OFF, 100} // off,
    },
    {
        {LED_ON, 100} // on
    },

    {
        {LED_OFF, 1000}, // slow blink
        {LED_ON, 1000},
    },

    {
        {LED_OFF, 500}, // normal blink
        {LED_ON, 500},
    },

    {
        {LED_OFF, 250}, // fast blink
        {LED_ON, 250},
    },

    {
        {LED_OFF, 1000}, // pulse
        {LED_ON, 250},
    },

    {{LED_OFF, 500}, // custom blink
     {LED_ON, 500},
     {LED_OFF, 250},
     {LED_ON, 250},
     {LED_OFF, 500},
     {LED_ON, 500},
     {LED_OFF, 1000},
     {LED_ON, 1000}}};

// Data Types - typedefs, structs, unions and/or enumerated
typedef struct
{
    unsigned char pin;
    unsigned char mode; // led mode
    unsigned char change;
} Led_t;

// Classes
class LedTask : public RTOSTaskTemplate<Led_t>
{
public:
    void setup(Led_t &pParameters) override
    {
        mPin = pParameters.pin;
        pinMode(mPin, OUTPUT);
        digitalWrite(mPin, LOW);

        mMode = pParameters.mode;
        mChange = pParameters.change;

        mModePtr = LED_MODES[mMode];
    }

    void setChange()
    {
        mChange = true;
    }

    void clear()
    {
        mMode = lmCustom;
        mChange = true;
    }

private:
    uint8_t mPin = 0;
    uint8_t mMode = lmClear;
    uint8_t mChange = false;
    const LedMode_t *mModePtr = nullptr;

protected:
    void execute() override
    {
        if (mChange)
        {
            mChange = false;
            ++mMode %= (lmCustom + 1);
            mModePtr = LED_MODES[mMode];
            Serial.printf("Led Mode: %d\n", mMode);
        }

        digitalWrite(mPin, mModePtr->state);
        vTaskDelay(pdMS_TO_TICKS(mModePtr->delay));

        mModePtr++;

        if (mModePtr->delay == 0)
        {
            mModePtr = LED_MODES[mMode];
        }
    }
};

// Public functions
void ledSetup(void);
void ledInit(void);
void ledChange(uint8_t pLed);
void ledClearAll(void);

// Local Variables
#ifdef _LED_

LedTask ledF1;
LedTask ledF2;

#endif
