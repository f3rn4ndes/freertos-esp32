/*
  Copyright (c), 2023
  All rights reserved.
*/

/* Defines */
#define _APP_

/* Includes */
#include "app.h"

/* Functions */

void appSetup(void)
{

    Serial.begin(APP_MONITOR_SPEED);
    ledsSetup();
    buttonsSetup();
}

void appInit(void)
{
    Serial.printf("----- START APPLICATION -----\n");
    appExample.create(
        "Teste",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        APP_TASK_LOOP,
        APP_TASK_DELAY_MS);
}

void AppTask::setup()
{
}

void AppTask::execute()
{
    uint32_t rv;

    for (;;)
    {
        if (appExample.getNotification())
        {
            rv = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        }

        Serial.println((String) "AppExample: " + __func__);

        if (!appExample.getNotification())
        {
            vTaskDelay(pdMS_TO_TICKS(appExample.getTaskDelay()));
        }
    }
}
