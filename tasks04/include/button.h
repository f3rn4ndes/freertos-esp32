#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systemtasks.h"
#include "board.h"
#include "led.h"
#include "verbose.h"
#include "rtostasktemplate.h"

// Defines
#define BUTTON_F1 (uint8_t) BOARD_BUTTON_F1_PIN
#define BUTTON_F2 (uint8_t) BOARD_BUTTON_F2_PIN
#define BUTTON_F3 (uint8_t) BOARD_BUTTON_F3_PIN

// External Objects

// Data Types - typedefs, structs, unions and/or enumerated
typedef enum
{
    bfChangeLed = 0,
    bfClearAll
} ButtonFunction_t;

typedef struct
{

    uint8_t pin;
    uint8_t led;
    ButtonFunction_t function;

} Button_t;

// Classes
class ButtonTask : public RTOSTaskTemplate<Button_t>
{
public:
    void setup(Button_t &pParameters) override
    {
        mPin = pParameters.pin;
        mLed = pParameters.led;
        mFunction = pParameters.function;
        pinMode(mPin, INPUT_PULLUP);
        mFree = true;
    }

private:
    uint8_t mPin = 0;
    uint8_t mLed = 0;
    ButtonFunction_t mFunction = bfChangeLed;
    uint8_t mFree = true;

protected:
    void execute() override
    {
        // check pressed
        if (!digitalRead(mPin) && mFree)
        {
            mFree = false;
            // Notify Led Module
            action();
        }

        // check released
        if (digitalRead(mPin) && !mFree)
        {
            mFree = true;
        }
    }

    void action()
    {
        switch (mFunction)
        {
        case bfChangeLed:
            ledChange(mLed);
            break;
        case bfClearAll:
            ledClearAll();
            break;
        }
    }
};

// Public Functions
void buttonSetup(void);
void buttonInit(void);
