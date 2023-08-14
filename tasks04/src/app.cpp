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
        "Teste 1",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        APP_TASK_LOOP,
        APP_TASK_DELAY_MS);

    appExample2.create(
        "Teste 2",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        APP_TASK_LOOP,
        APP_TASK_DELAY_MS * 2);

    appExample3.create(
        "Teste 3",
        APP_TASK_STACK_SIZE,
        APP_TASK_PRIORITY,
        APP_TASK_CORE,
        APP_TASK_LOOP,
        APP_TASK_DELAY_MS * 5);
}
