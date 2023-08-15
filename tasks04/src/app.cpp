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
    Serial.printf("----- START APPLICATION -----\n");

    ledSetup();
    ledInit();

    buttonSetup();
    buttonInit();

    appExample.create(
        "Teste 1",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        SYSTEM_TASK_LOOP,
        APP_TASK_DELAY_MS);

    appExample2.create(
        "Teste 2",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        SYSTEM_TASK_LOOP,
        APP_TASK_DELAY_MS * 2);
}
