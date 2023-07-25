/*
  Copyright (c), 2023
  All rights reserved.
*/

/* Defines */
#define _LEDS_

/* Includes */
#include "leds.h"

/* Functions */

void ledsSetup(void)
{

	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);

	ledsInit();
}

void ledsInit(void)
{

	led1.pin = LED1;
	led1.mode = lmClear;
	led1.change = false;

	led2.pin = LED2;
	led2.mode = lmClear;
	led2.change = false;

	leds1TaskCreate();
	leds2TaskCreate();
}

void leds1TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		leds1Task,			  // task function
		"LEDS1",			  // task name
		LED1_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
		NULL,				  // task parameters (not used) (see systemtasks.h)
		LED1_TASK_PRIORITY,	  // task priority (see systemtasks.h)
		&leds1TaskHandle,	  // task handle
		LED1_TASK_CORE		  // core processor where the task will be run (see systemtasks.h)
	);
	assert(rc == pdPASS);
}

void leds2TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		leds2Task,			  // task function
		"LEDS2",			  // task name
		LED2_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
		NULL,				  // task parameters (not used) (see systemtasks.h)
		LED2_TASK_PRIORITY,	  // task priority (see systemtasks.h)
		&leds2TaskHandle,	  // task handle
		LED2_TASK_CORE		  // core processor where the task will be run (see systemtasks.h)
	);
	assert(rc == pdPASS);
}

static void leds1Task(void *pvParameters)
{
	static const xLedMode *ptr = LED_MODES[led1.mode];
	for (;;)
	{
		if (led1.change)
		{
			led1.change = false;
			++led1.mode %= (lmCustom + 1);
			ptr = LED_MODES[led1.mode];
			Serial.printf("Led 1 Mode: %d\n", led1.mode);
		}

		digitalWrite(LED1, ptr->state);
		vTaskDelay(pdMS_TO_TICKS(ptr->delay));

		ptr++;

		if (ptr->delay == 0)
		{
			ptr = LED_MODES[led1.mode];
		}
	}
}

static void leds2Task(void *pvParameters)
{
	static const xLedMode *ptr = LED_MODES[led1.mode];
	for (;;)
	{
		if (led2.change)
		{
			led2.change = false;
			++led2.mode %= (lmCustom + 1);
			ptr = LED_MODES[led2.mode];
			Serial.printf("Led 2 Mode: %d\n", led2.mode);
		}

		digitalWrite(LED2, ptr->state);
		vTaskDelay(pdMS_TO_TICKS(ptr->delay));

		ptr++;

		if (ptr->delay == 0)
		{
			ptr = LED_MODES[led2.mode];
		}
	}
}

void led1Change(void)
{
	led1.change = true;
}

void led2Change(void)
{
	led2.change = true;
}
