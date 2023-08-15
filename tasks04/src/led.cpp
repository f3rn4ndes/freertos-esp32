/*
  Copyright (c), 2023
  All rights reserved.
*/

// Defines
#define _LED_

// Includes
#include "led.h"

// Functions

void ledSetup(void)
{
    Led_t _leds;

    _leds.pin = LED_F1;
    _leds.mode = lmClear;
    _leds.change = false;

    ledF1.setup(_leds);

    _leds.pin = LED_F2;
    _leds.mode = lmClear;
    _leds.change = false;

    ledF2.setup(_leds);
}

void ledInit(void)
{
    ledF1.create("Led F1", LED_F1_TASK_STACK_SIZE, LED_F1_TASK_PRIORITY, LED_F1_TASK_CORE, false, 0);
    ledF2.create("Led F2", LED_F2_TASK_STACK_SIZE, LED_F2_TASK_PRIORITY, LED_F2_TASK_CORE, false, 0);
}

TaskHandle_t ledGetTaskHandle(uint8_t pTaskHandle)
{
    TaskHandle_t _taskHandle = nullptr;

    switch (pTaskHandle)
    {
    case LED_F1:
        _taskHandle = ledF1.getTaskHandle();
        break;
    case LED_F2:
        _taskHandle = ledF2.getTaskHandle();
        break;
    }
    return _taskHandle;
}

// static void leds1Task(void *pvParameters)
// {
//     static const xLedMode *ptr = LED_MODES[led1.mode];
//     for (;;)
//     {
//         if (led1.change)
//         {
//             led1.change = false;
//             ++led1.mode %= (lmCustom + 1); // 0..1....6..(in 7 back to 0)
//             ptr = LED_MODES[led1.mode];
//             Serial.printf("Led 1 Mode: %d\n", led1.mode);
//         }

//         digitalWrite(LED1, ptr->state);
//         vTaskDelay(pdMS_TO_TICKS(ptr->delay));

//         ptr++;

//         if (ptr->delay == 0)
//         {
//             ptr = LED_MODES[led1.mode];
//         }
//     }
// }

// static void leds2Task(void *pvParameters)
// {
//     static const xLedMode *ptr = LED_MODES[led1.mode];
//     for (;;)
//     {
//         if (led2.change)
//         {
//             led2.change = false;
//             ++led2.mode %= (lmCustom + 1);
//             ptr = LED_MODES[led2.mode];
//             Serial.printf("Led 2 Mode: %d\n", led2.mode);
//         }

//         digitalWrite(LED2, ptr->state);
//         vTaskDelay(pdMS_TO_TICKS(ptr->delay));

//         ptr++;

//         if (ptr->delay == 0)
//         {
//             ptr = LED_MODES[led2.mode];
//         }
//     }
// }

// void led1Change(void)
// {
//     led1.change = true;
// }

// void led2Change(void)
// {
//     led2.change = true;
// }
