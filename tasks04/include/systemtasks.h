/*
  Copyright (c), 2023
  All rights reserved.
*/

#pragma once

// Defines

#define SYSTEM_TASK_LOOP false
#define SYSTEM_TASK_NOTIFY true

// Task Stack Size
#define APP_DEFAULT_STACK_SIZE 3000
#define APP_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE

#define LED_F1_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE
#define LED_F2_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE
#define BUTTON_F1_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE
#define BUTTON_F2_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE

// Task Priority
#define APP_TASK_PRIORITY 1

#define LED_F1_TASK_PRIORITY 3
#define LED_F2_TASK_PRIORITY 3
#define BUTTON_F1_TASK_PRIORITY 4
#define BUTTON_F2_TASK_PRIORITY 5

// Tasks Core
#define APP_TASK_CORE 0

#define LED_F1_TASK_CORE 0
#define LED_F2_TASK_CORE 0
#define BUTTON_F1_TASK_CORE 0
#define BUTTON_F2_TASK_CORE 0

// Tasks Delay
#define APP_TASK_DELAY_MS 1000

#define BUTTON_F1_TASK_DELAY_MS 25
#define BUTTON_F2_TASK_DELAY_MS 25
