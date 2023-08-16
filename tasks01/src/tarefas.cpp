/*
  Copyright (c), 2023
  All rights reserved.
*/

// Defines
#define _TAREFAS_

// Includes
#include "tarefas.h"

/* Functions */

void tarefasSetup(void)
{
	// Criacao das tarefas
	// void tarefasTaskCreate(); <--- nao pode esse void aqui
	tarefasTaskCreate();
}

void tarefasInit(void)
{
}

void tarefasTaskCreate(void)
{
	tarefas1TaskCreate();
	tarefas2TaskCreate();
	tarefas3TaskCreate();
	tarefas4TaskCreate();
}

void tarefasSystemTasksCreate(void)
{

}

void tarefasResumeTasks(void)
{
	vTaskResume(tarefas1TaskHandle);
	vTaskResume(tarefas2TaskHandle);
	vTaskResume(tarefas3TaskHandle);
}

static void tarefasTask(void *pvParameters)
{

}

void tarefas1TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		tarefas1Task,			  // nome da funcao da tarefa que vai ser executada
		"TAREFAS1",				  // nome da tarefa
		TAREFAS1_TASK_STACK_SIZE, // tamanho da memoria para executar a tarefa
		NULL,					  // parâmetros da tarefa, ou nulo
		TAREFAS1_TASK_PRIORITY,	  // prioridade da tarefa
		&tarefas1TaskHandle,	  // handle da tarefa ou nulo
		TAREFAS1_TASK_CORE		  // core do processador onde vai ser executada a tarefa
	);
	assert(rc == pdPASS);
	vTaskSuspend(tarefas1TaskHandle);
}

void tarefas2TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		tarefas2Task,			  // nome da funcao da tarefa que vai ser executada
		"TAREFAS2",				  // nome da tarefa
		TAREFAS2_TASK_STACK_SIZE, // tamanho da memoria para executar a tarefa
		NULL,					  // parâmetros da tarefa, ou nulo
		TAREFAS2_TASK_PRIORITY,	  // prioridade da tarefa
		&tarefas2TaskHandle,	  // handle da tarefa ou nulo
		TAREFAS2_TASK_CORE		  // core do processador onde vai ser executada a tarefa
	);
	assert(rc == pdPASS);
	vTaskSuspend(tarefas2TaskHandle);
}

void tarefas3TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		tarefas3Task,			  // nome da funcao da tarefa que vai ser executada
		"TAREFAS3",				  // nome da tarefa
		TAREFAS3_TASK_STACK_SIZE, // tamanho da memoria para executar a tarefa
		NULL,					  // parâmetros da tarefa, ou nulo
		TAREFAS3_TASK_PRIORITY,	  // prioridade da tarefa
		&tarefas3TaskHandle,	  // handle da tarefa ou nulo
		TAREFAS3_TASK_CORE		  // core do processador onde vai ser executada a tarefa
	);
	assert(rc == pdPASS);
	vTaskSuspend(tarefas3TaskHandle);
}

void tarefas4TaskCreate(void)
{
	BaseType_t rc;
	rc = xTaskCreatePinnedToCore(
		tarefas4Task,			  // nome da funcao da tarefa que vai ser executada
		"TAREFAS4",				  // nome da tarefa
		TAREFAS4_TASK_STACK_SIZE, // tamanho da memoria para executar a tarefa
		NULL,					  // parâmetros da tarefa, ou nulo
		TAREFAS4_TASK_PRIORITY,	  // prioridade da tarefa
		&tarefas4TaskHandle,	  // handle da tarefa ou nulo
		TAREFAS4_TASK_CORE		  // core do processador onde vai ser executada a tarefa
	);
	assert(rc == pdPASS);

	vTaskSuspend(tarefas4TaskHandle);
}

static void tarefas1Task(void *pvParameters)
{
	static int contador = 0;
	for (;;)
	{
		Serial.printf("Tarefa 1 - Contador: %d\n", ++contador);
		vTaskDelay(pdMS_TO_TICKS(TAREFAS1_TASK_DELAY_MS));
	}
	vTaskDelete(NULL);
}

static void tarefas2Task(void *pvParameters)
{
	static int contador = 0;

	for (;;)
	{
		Serial.printf(">> Tarefa 2 - Contador: %d\n", ++contador);

		// sempre que o resto da divisao de contador por 5 = 0 chama a tarefa 3
		if (contador % 5 == 0) // 5 10 15 ...
		{
			xTaskNotifyGive(tarefas3TaskHandle);
		}

		// sempre que o resto da divisao de contador por 7 = 0 chama a tarefa 4
		if (contador % 7 == 0) // 7 14 21 ...
		{
			if (eTaskGetState(tarefas4TaskHandle) == eSuspended)
			{
				vTaskResume(tarefas4TaskHandle);
			}
		}

		vTaskDelay(pdMS_TO_TICKS(TAREFAS2_TASK_DELAY_MS));
	}
	vTaskDelete(NULL);
}

// tarefa 3 roda e aguarda notificação
static void tarefas3Task(void *pvParameters)
{
	uint32_t rv;
	static int contador = 0;
	for (;;)
	{
		rv = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		Serial.printf("-------------------------- Tarefa 3 - Contador: %d\n", ++contador);
		vTaskDelay(pdMS_TO_TICKS(TAREFAS3_TASK_DELAY_MS));
	}
	vTaskDelete(NULL);
}

// tarefa 4 executa e suspende
static void tarefas4Task(void *pvParameters)
{
	static int contador = 0;
	for (;;)
	{
		Serial.printf("************************* Tarefa 4 - Contador: %d\n", ++contador);
		vTaskSuspend(tarefas4TaskHandle);
	}
	vTaskDelete(NULL);
}

