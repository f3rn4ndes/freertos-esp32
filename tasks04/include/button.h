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

// Classes
class ButtonTask : public RTOSTaskTemplate<uint8_t>
{
public:
    void setup(uint8_t &pButtonPin) override
    {
        mPin = pButtonPin;
        pinMode(mPin, INPUT_PULLUP);
    }

    void createNotifier(TaskHandle_t pTask)
    {
        mTargetTask = pTask;
        mNotifyTargetTask = true;
    }

private:
    uint8_t mPin = 0;

    TaskHandle_t mTargetTask = nullptr;
    boolean mNotifyTargetTask = false;

protected:
    void execute() override
    {
        static int _free = true;

        // check pressed
        if (!digitalRead(mPin) && _free)
        {
            _free = false;
            // notify the corresponding led task
            if (mNotifyTargetTask)
            {
                xTaskNotifyGive(mTargetTask);
            }
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

void buttonF1SetNotifier(TaskHandle_t &pTaskHandle);
void buttonF2SetNotifier(TaskHandle_t &pTaskHandle);

// Local Variables
#ifdef _BUTTON_

ButtonTask buttonF1;
ButtonTask buttonF2;

#endif
