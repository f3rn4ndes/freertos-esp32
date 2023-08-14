/*
  Copyright (c), 2023
  All rights reserved.
*/

/* Defines */
#define _BUTTONS_

/* Includes */
#include "buttons.h"

/* Functions */

void buttonsSetup(void)
{

    pinMode(BUTTON1, INPUT_PULLUP);
    pinMode(BUTTON2, INPUT_PULLUP);

    buttonsInit();
}

void buttonsInit(void)
{
    button1TaskCreate();
    button2TaskCreate();

    myButtonMozovos.create("meu botao", 4000, 4, 1, false, 500);
}

void button1TaskCreate(void)
{
    BaseType_t rc;
    rc = xTaskCreatePinnedToCore(
        button1Task,             // task function
        "BUTTON1",               // task name
        BUTTON1_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
        NULL,                    // task parameters (not used) (see systemtasks.h)
        BUTTON1_TASK_PRIORITY,   // task priority (see systemtasks.h)
        &button1TaskHandle,      // task handle
        BUTTON1_TASK_CORE        // core processor where the task will be run (see systemtasks.h)
    );
    assert(rc == pdPASS);
}

void button2TaskCreate(void)
{
    BaseType_t rc;
    rc = xTaskCreatePinnedToCore(
        button2Task,             // task function
        "BUTTON2",               // task name
        BUTTON2_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
        NULL,                    // task parameters (not used) (see systemtasks.h)
        BUTTON2_TASK_PRIORITY,   // task priority (see systemtasks.h)
        &button2TaskHandle,      // task handle
        BUTTON1_TASK_CORE        // core processor where the task will be run (see systemtasks.h)
    );
    assert(rc == pdPASS);
}

static void button1Task(void *pvParameters)
{
    static int free = true;
    for (;;)
    {
        // check pressed
        if (!digitalRead(BUTTON1) && free)
        {
            free = false;
            led1Change();
        }

        // check released
        if (digitalRead(BUTTON1) && !free)
        {
            free = true;
        }
        vTaskDelay(pdMS_TO_TICKS(BUTTON1_TASK_DELAY_MS));
    }
}

static void button2Task(void *pvParameters)
{
    static int free = true;
    for (;;)
    {
        // check pressed
        if (!digitalRead(BUTTON2) && free)
        {
            free = false;
            led2Change();
        }

        // check released
        if (digitalRead(BUTTON2) && !free)
        {
            free = true;
        }
        vTaskDelay(pdMS_TO_TICKS(BUTTON2_TASK_DELAY_MS));
    }
}
