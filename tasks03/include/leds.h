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
#include "board.h"

/* Defines */
#define LED1 BOARD_LED1_PIN
#define LED2 BOARD_LED2_PIN

/* Data Types - typedefs, structs, unions and/or enumerated */
#define LEDMODE_MAX_ITENS 10

typedef enum
{
	lmClear = 0,
	lmSolid,
	lmSlowBlink,
	lmBlink,
	lmFastBlink,
	lmCustom
} enLedMode;

// led modes
typedef struct
{
	unsigned char state;
	unsigned int delay;
} xLedMode;

typedef struct
{
	unsigned char pin;
	unsigned char mode;
	unsigned char change;
} xLed;

const xLedMode LED_MODES[][LEDMODE_MAX_ITENS] = {
	{
		{0, 100} // off
	},
	{
		{1, 100} // on
	},

	{
		{0, 1000}, // slow blink
		{1, 1000},
	},

	{
		{0, 500}, // normal blink
		{1, 500},
	},

	{
		{0, 2000}, // fast blink, aka pulse
		{1, 250},
	},

	{{0, 500}, // custom blink
	 {1, 500},
	 {0, 250},
	 {1, 250},
	 {0, 500},
	 {1, 500},
	 {0, 1000},
	 {1, 1000}}};

/* Public Functions */
void ledsSetup(void);

void led1Change(void);
void led2Change(void);

/* Local Functions */
#ifdef _LEDS_

void ledsInit(void);

void leds1TaskCreate(void);
void leds2TaskCreate(void);

static void leds1Task(void *pvParameters);
static void leds2Task(void *pvParameters);

#endif

/* Public Variables */

/* Local Variables */
#ifdef _LEDS_

xLed led1, led2;

static TaskHandle_t leds1TaskHandle = NULL;
static TaskHandle_t leds2TaskHandle = NULL;

#endif

#endif