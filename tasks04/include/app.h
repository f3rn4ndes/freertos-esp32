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
#include "led.h"
#include "button.h"

// Defines
#define APP_INITIAL_DELAY_MS 2000
#define APP_MONITOR_SPEED 115200

// Data Types - typedefs, structs, unions and/or enumerated

// Classes
class AppTask : public RTOSTaskTemplate<int>
{

protected:
    void execute() override
    {
        Serial.println((String) "Task: " + getTaskName() + " - Task Delay: " + getTaskDelay());
    }
};

// Public Functions
void appSetup(void);

// Local Variables and Objects
#ifdef _APP_
AppTask appExample;
AppTask appExample2;
#endif
