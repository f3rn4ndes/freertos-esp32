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
typedef struct
{
    TaskHandle_t taskHandle;
} AppNotify_t;

// Classes
class AppTask : public RTOSTaskTemplate<AppNotify_t>
{

public:
    void setup(AppNotify_t &pParameters) override
    {
        mTaskHandleNotifier = pParameters.taskHandle;
        mNotification = true;
    }

private:
    TaskHandle_t mTaskHandleNotifier = nullptr;
    boolean mNotification = false;

protected:
    void execute() override
    {
        Serial.println((String) "Task: " + getTaskName() + " - Task Delay: " + getTaskDelay());
        action();
    }

    void action()
    {
        if (mNotification)
            xTaskNotifyGive(mTaskHandleNotifier);
    }
};

// Public Functions
void appSetup(void);
void appInit(void);

// Local Variables and Objects
#ifdef _APP_
AppTask appTaskLoop1;
AppTask appTaskLoop2;
AppTask appTaskNotify;

#endif
