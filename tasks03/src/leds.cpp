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
	pinMode(LED1_PIN, OUTPUT);
	pinMode(LED2_PIN, OUTPUT);
	pinMode(LED3_PIN, OUTPUT);
	pinMode(LED4_PIN, OUTPUT);
	digitalWrite(LED1_PIN, LOW);
	digitalWrite(LED2_PIN, LOW);
	digitalWrite(LED3_PIN, LOW);
	digitalWrite(LED4_PIN, LOW);

	ledsInit();

}

void ledsInit(void)
{
	leds1TaskCreate();
	leds2TaskCreate();
	leds3TaskCreate();
	leds4TaskCreate();
}


void ledsResumeTasks(void)
{
	vTaskResume(leds1TaskHandle);
	vTaskResume(leds2TaskHandle);
	vTaskResume(leds3TaskHandle);
}

void leds1TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		leds1Task,			      // task function
		"LEDS1",				  // task name
		LEDS1_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
		NULL,					  // task parameters (not used) (see systemtasks.h)
		LEDS1_TASK_PRIORITY,	  // task priority (see systemtasks.h)
		&leds1TaskHandle,	  // task handle
		LEDS1_TASK_CORE		  // core processor where the task will be run (see systemtasks.h)
	);
	assert(rc == pdPASS);
	vTaskSuspend(leds1TaskHandle);
}

void leds2TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		leds2Task,			      // task function
		"LEDS2",				  // task name
		LEDS2_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
		NULL,					  // task parameters (not used) (see systemtasks.h)
		LEDS2_TASK_PRIORITY,	  // task priority (see systemtasks.h)
		&leds2TaskHandle,	  // task handle
		LEDS1_TASK_CORE		  // core processor where the task will be run (see systemtasks.h)
	);
	assert(rc == pdPASS);
	vTaskSuspend(leds2TaskHandle);
}

void leds3TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		leds3Task,			      // task function
		"LEDS3",				  // task name
		LEDS3_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
		NULL,					  // task parameters (not used) (see systemtasks.h)
		LEDS3_TASK_PRIORITY,	  // task priority (see systemtasks.h)
		&leds3TaskHandle,	  // task handle
		LEDS3_TASK_CORE		  // core processor where the task will be run (see systemtasks.h)
	);
	assert(rc == pdPASS);
	vTaskSuspend(leds3TaskHandle);
}

void leds4TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		leds4Task,			      // task function
		"LEDS4",				  // task name
		LEDS4_TASK_STACK_SIZE, // stack size, memory size to run this task (see systemtasks.h)
		NULL,					  // task parameters (not used) (see systemtasks.h)
		LEDS4_TASK_PRIORITY,	  // task priority (see systemtasks.h)
		&leds4TaskHandle,	  // task handle
		LEDS4_TASK_CORE		  // core processor where the task will be run (see systemtasks.h)
	);
	assert(rc == pdPASS);
	vTaskSuspend(leds4TaskHandle);
}

static void leds1Task(void *pvParameters)
{
	for (;;)
	{
		// blink led 1
		digitalWrite(LED1_PIN,digitalRead(LED1_PIN)^1);
		vTaskDelay(pdMS_TO_TICKS(LEDS1_TASK_DELAY_MS));
	}
	vTaskDelete(NULL);
}

static void leds2Task(void *pvParameters)
{
	static int taskCounter = 0;

	for (;;)
	{
		++taskCounter;

		// blink led 2
		digitalWrite(LED2_PIN,digitalRead(LED2_PIN)^1);

		if (taskCounter % 5 == 0) // 5 10 15 ...
		{
			xTaskNotifyGive(leds3TaskHandle);
		}

		if (taskCounter % 7 == 0) // 7 14 21 ...
		{
			if (eTaskGetState(leds4TaskHandle) == eSuspended)
			{
				vTaskResume(leds4TaskHandle);
			}
		}

		vTaskDelay(pdMS_TO_TICKS(LEDS2_TASK_DELAY_MS));
	}
	vTaskDelete(NULL);
}

// Task 3 : Wait Notification
static void leds3Task(void *pvParameters)
{
	uint32_t rv;
	for (;;)
	{
		rv = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		// blink led 3
		digitalWrite(LED3_PIN,digitalRead(LED3_PIN)^1);
		// vTaskDelay(pdMS_TO_TICKS(LEDS3_TASK_DELAY_MS));
	}
	vTaskDelete(NULL);
}

// Task 4 : Executes and Suspend
static void leds4Task(void *pvParameters)
{
	for (;;)
	{
		// blink led 4
		digitalWrite(LED4_PIN,digitalRead(LED4_PIN)^1);
		vTaskSuspend(leds4TaskHandle);
	}
	vTaskDelete(NULL);
}

