#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtostasktemplate.h"
#include "led.h"
#include "button.h"
#include "verbose.h"
#include "sysclock.h"

// Defines
#define APP_INITIAL_DELAY_MS 2000
#define APP_MONITOR_SPEED 115200

// External Objects
extern LedTask ledF1;
extern LedTask ledF2;
extern VerboseTask verbose;
extern ButtonTask buttonF1;
extern ButtonTask buttonF2;
extern ButtonTask buttonF3;

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
        mApp = pParameters;

        mNotification = (mApp.taskHandle != nullptr) ? true : false;
    }

private:
    AppNotify_t mApp;

    boolean mNotification = false;

protected:
    void execute() override
    {
        VERBOSE((String) "Task: " + getTaskName() + " - Task Delay: " + getTaskDelay(), VERBOSE_TASK_APP);
        action();
    }

    void action()
    {
        if (mNotification)
        {
            sysClockTimerMSShowElapse(ctTimer01, CLOCK_TIMER_RESET);
            VERBOSE((String) "Task: " + getTaskName() + " - Notify Task: " + pcTaskGetName(mApp.taskHandle), VERBOSE_TASK_APP);
            xTaskNotifyGive(mApp.taskHandle);
        }
    }
};

// Public Functions
void appSetup(void);
void appInit(void);
