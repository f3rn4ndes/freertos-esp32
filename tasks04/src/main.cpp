/*
  Copyright (c), 2023
  All rights reserved.
*/

// Defines
#define _MAIN_

// Includes
#include "main.h"

// Functions

void setup()
{
    // put your setup code here, to run once:
    vTaskDelay(pdMS_TO_TICKS(APP_INITIAL_DELAY_MS));
    appSetup();
    appInit();
}

// Delete Task
void loop()
{
    // Delete Loop Task
    vTaskDelete(NULL);
}
