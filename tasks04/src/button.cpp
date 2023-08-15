/*
  Copyright (c), 2023
  All rights reserved.
*/

// Defines
#define _BUTTON_

// Includes
#include "button.h"

// Functions

void buttonSetup(void)
{
    uint8_t _button;

    _button = BUTTON_F1;
    buttonF1.setup(_button);

    _button = BUTTON_F1;
    buttonF2.setup(_button);
}

void buttonInit(void)
{

    buttonF1.createNotifier(ledGetTaskHandle(LED_F1));
    buttonF2.createNotifier(ledGetTaskHandle(LED_F2));

    buttonF1.create(
        "BUTTON F1",
        BUTTON_F1_TASK_STACK_SIZE,
        BUTTON_F1_TASK_PRIORITY,
        BUTTON_F1_TASK_CORE,
        SYSTEM_TASK_NOTIFY,
        BUTTON_F1_TASK_DELAY_MS);

    buttonF2.create(
        "BUTTON F2",
        BUTTON_F2_TASK_STACK_SIZE,
        BUTTON_F2_TASK_PRIORITY,
        BUTTON_F2_TASK_CORE,
        SYSTEM_TASK_NOTIFY,
        BUTTON_F2_TASK_DELAY_MS);
}

