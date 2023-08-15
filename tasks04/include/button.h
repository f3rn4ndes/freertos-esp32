/*
  Copyright (c), 2023
  All rights reserved.
*/
#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systemtasks.h"
#include "board.h"
#include "led.h"
#include "rtostasktemplate.h"

// Defines
#define BUTTON_F1 (uint8_t) BOARD_BUTTON_F1_PIN
#define BUTTON_F2 (uint8_t) BOARD_BUTTON_F2_PIN

// Data Types - typedefs, structs, unions and/or enumerated
typedef struct
{

    uint8_t pin;
    uint8_t led;

} Button_t;

// Classes
class ButtonTask : public RTOSTaskTemplate<Button_t>
{
public:
    void setup(Button_t &pParameters) override
    {
        mPin = pParameters.pin;
        mLed = pParameters.led;
        pinMode(mPin, INPUT_PULLUP);
    }

private:
    uint8_t mPin = 0;
    uint8_t mLed = 0;

protected:
    void execute() override
    {
        static int _free = true;

        // check pressed
        if (!digitalRead(mPin) && _free)
        {
            _free = false;
            // Notify Led Module
            ledChange(mLed);
        }

        // check released
        if (digitalRead(mPin) && !_free)
        {
            _free = true;
        }
    }
};

// Public Functions
void buttonSetup(void);
void buttonInit(void);

// Local Variables
#ifdef _BUTTON_

ButtonTask buttonF1;
ButtonTask buttonF2;

#endif
