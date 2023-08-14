/*
  Copyright (c), 2023
  All rights reserved.
*/
#pragma once

/* Includes */
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systemtasks.h"
#include "board.h"
#include "leds.h"
#include "rtostasktemplate.h"

/* Defines */
#define BUTTON1 BOARD_BUTTON1_PIN
#define BUTTON2 BOARD_BUTTON2_PIN

/* Data Types - typedefs, structs, unions and/or enumerated */

// Classes
class ButtonTask : public RTOSTaskTemplate
{
protected:
    void setup() override
    {
    }

    void execute() override
    {
        uint32_t rv;

        for (;;)
        {
            if (this->getNotification())
            {
                rv = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            }

            Serial.println((String) "Botão: " + this->getTaskName() + " - Task Delay: " + this->getTaskDelay());

            if (!this->getNotification())
            {
                vTaskDelay(pdMS_TO_TICKS(this->getTaskDelay()));
            }
        }
    }
};

/* Public Functions */
void buttonsSetup(void);

/* Local Functions */
#ifdef _BUTTONS_

void buttonsInit(void);

void button1TaskCreate(void);
void button2TaskCreate(void);

static void button1Task(void *pvParameters);
static void button2Task(void *pvParameters);

#endif

/* Public Variables */

/* Local Variables */
#ifdef _BUTTONS_

static TaskHandle_t button1TaskHandle = NULL;
static TaskHandle_t button2TaskHandle = NULL;

ButtonTask myButtonMozovos;

#endif
