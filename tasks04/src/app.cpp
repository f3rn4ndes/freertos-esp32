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
    verboseSetup();
    verboseInit();

    VERBOSE((String) "----- START APPLICATION -----", VERBOSE_MODULE_APP);
}

void appInit(void)
{
    AppNotify_t _task;

    VERBOSE((String) "Function: " + __func__, VERBOSE_MODULE_APP);

    ledSetup();
    ledInit();

    buttonSetup();
    buttonInit();

    appTaskLoop1.create(
        "Task Loop 1",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        SYSTEM_TASK_LOOP,
        APP_TASK_DELAY_MS);

    appTaskNotify.create(
        "Task Notify",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        SYSTEM_TASK_NOTIFY,
        0);

    _task.taskHandle = appTaskNotify.getTaskHandle();
    appTaskLoop2.setup(_task);

    appTaskLoop2.create(
        "Task Loop 2",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        SYSTEM_TASK_LOOP,
        APP_TASK_DELAY_MS * 3);
}
