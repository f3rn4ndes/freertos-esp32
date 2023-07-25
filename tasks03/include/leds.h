/*
  Copyright (c), 2023
  All rights reserved.
*/
#ifndef LEDS_H
#define LEDS_H

/* Includes */
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systemtasks.h"

/* Defines */
#define LED1_PIN GPIO_NUM_21
#define LED2_PIN GPIO_NUM_19
#define LED3_PIN GPIO_NUM_18
#define LED4_PIN GPIO_NUM_17

/* Data Types - typedefs, structs, unions and/or enumerated */

/* Public Functions */
void ledsSetup(void);
void ledsResumeTasks(void);

/* Local Functions */
#ifdef _LEDS_

	void ledsInit(void);

	void leds1TaskCreate(void);
	void leds2TaskCreate(void);
	void leds3TaskCreate(void);
	void leds4TaskCreate(void);

	static void leds1Task(void *pvParameters);
	static void leds2Task(void *pvParameters);
	static void leds3Task(void *pvParameters);
	static void leds4Task(void *pvParameters);

#endif

/* Public Variables */

/* Local Variables */
#ifdef _LEDS_

	static TaskHandle_t leds1TaskHandle = NULL;
	static TaskHandle_t leds2TaskHandle = NULL;
	static TaskHandle_t leds3TaskHandle = NULL;
	static TaskHandle_t leds4TaskHandle = NULL;

#endif

#endif