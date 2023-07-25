/*
  Copyright (c), 2023
  All rights reserved.
*/

#ifndef SYSTEMTASKS_H
#define SYSTEMTASKS_H

/* Defines */
/* Task Stack Size */
#define APP_DEFAULT_STACK_SIZE 3000
#define APP_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE

#define LEDS1_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE
#define LEDS2_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE
#define LEDS3_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE
#define LEDS4_TASK_STACK_SIZE APP_DEFAULT_STACK_SIZE


/* Task Priority */
#define APP_TASK_PRIORITY 1

#define LEDS1_TASK_PRIORITY 6
#define LEDS2_TASK_PRIORITY 4 
#define LEDS3_TASK_PRIORITY 5
#define LEDS4_TASK_PRIORITY 5

/* Tasks Core */
#define APP_TASK_CORE 0

#define LEDS1_TASK_CORE 0
#define LEDS2_TASK_CORE 0
#define LEDS3_TASK_CORE 0
#define LEDS4_TASK_CORE 0


/* Tasks Delay */
#define APP_TASK_DELAY_MS 50


#define LEDS1_TASK_DELAY_MS 500
#define LEDS2_TASK_DELAY_MS 1000
#define LEDS3_TASK_DELAY_MS 10
#define LEDS4_TASK_DELAY_MS 10

#endif // #define SYSTEMTASKS_H