/*
  Copyright (c), 2023
  All rights reserved.
*/
#ifndef APP_H
#define APP_H

/* Includes */
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "leds.h"


/* Defines */
#define APP_LOOP_DELAY_MS     2000
#define APP_INITIAL_DELAY_MS  2000
#define APP_MONITOR_SPEED     115200

/* Data Types - typedefs, structs, unions and/or enumerated */

/* Public Functions */
void appSetup(void);
void appInit(void);

/* Local Functions */
#ifdef _APP_


#endif

/* Public Variables */

/* Local Variables */
#ifdef _APP_

#endif

#endif