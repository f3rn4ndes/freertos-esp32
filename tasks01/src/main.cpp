/*
  Copyright (c), 2023
  All rights reserved.
*/

/* Defines */
#define _MAIN_

/* Includes */
#include "main.h"

/* Functions */

void setup()
{
	// put your setup code here, to run once:
	vTaskDelay(pdMS_TO_TICKS(APP_INITIAL_DELAY_MS));
	appSetup();
}

// Delete Task
void loop()
{

	vTaskDelay(pdMS_TO_TICKS(APP_LOOP_DELAY_MS));

	Serial.printf("\n\n<<<<<<<<<<<<<<< INICIANDO TAREFAS >>>>>>>>>>>>>>>>\n\n");

	vTaskDelay(pdMS_TO_TICKS(APP_LOOP_DELAY_MS));

	appInit();

	Serial.printf("\n\n<<<<<<<<<<<<<<< FINALIZANDO TAREFA DE LOOP >>>>>>>>>>>>>>>>\n\n");
	// Delete Loop Task
	vTaskDelete(NULL);

}
