/*
  Copyright (c), 2023
  All rights reserved.
*/
#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "leds.h"
#include "buttons.h"
#include "rtostasktemplate.h"

// Defines
#define APP_INITIAL_DELAY_MS 2000
#define APP_MONITOR_SPEED 115200

// Data Types - typedefs, structs, unions and/or enumerated

// Classes
class AppTask : public RTOSTaskTemplate
{
protected:
    void setup() override;
    void execute() override;
};

// Public Functions
void appSetup(void);
void appInit(void);

// Local Functions
#ifdef _APP_

#endif

// Public Variables

// Local Variables and Objects
#ifdef _APP_

AppTask appExample;

#endif
