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
  tarefasSetup();
}

void appInit(void)
{
  tarefasResumeTasks();  
}

void appTaskCreate(void)
{

}

void appSystemTasksCreate(void)
{

}

static void appTask(void *pvParameters)
{

}

