/*
  Copyright (c), 2023
  All rights reserved.
*/
#ifndef TAREFAS_H
#define TAREFAS_H

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systemtasks.h"

// Defines

// Data Types - typedefs, structs, unions and/or enumerated

// Public Functions
void tarefasSetup(void);
void tarefasResumeTasks(void);

// Local Functions
#ifdef _TAREFAS_

	void tarefasInit(void);

	void tarefasTaskCreate(void);

	void tarefas1TaskCreate(void);
	void tarefas2TaskCreate(void);
	void tarefas3TaskCreate(void);
	void tarefas4TaskCreate(void);

	static void tarefas1Task(void *pvParameters);
	static void tarefas2Task(void *pvParameters);
	static void tarefas3Task(void *pvParameters);
	static void tarefas4Task(void *pvParameters);

#endif

// Public Variables

// Local Variables
#ifdef _TAREFAS_

	static TaskHandle_t tarefasTaskHandle = NULL;

	static TaskHandle_t tarefas1TaskHandle = NULL;
	static TaskHandle_t tarefas2TaskHandle = NULL;
	static TaskHandle_t tarefas3TaskHandle = NULL;
	static TaskHandle_t tarefas4TaskHandle = NULL;

#endif

#endif