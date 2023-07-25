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
}

void appInit(void)
{
  ledsResumeTasks();  
}


