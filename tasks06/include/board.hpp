#pragma once

#include <Arduino.h>

// Boards
#define BOARD_DEPLOY 0     // Deploy
#define BOARD_DEVELOP_01 1 // Homologation
#define BOARD_DEVELOP_02 2
#define BOARD_DEVELOP_03 3

#define BOARD_ID BOARD_DEVELOP_01

// Factory Button
#if (BOARD_ID == BOARD_DEPLOY)

#define TEST_BUTTON_PIN GPIO_NUM_15

#endif

#if (BOARD_ID == BOARD_DEVELOP_01)

#define TEST_BUTTON_PIN GPIO_NUM_15

#endif

// Status Led
#if (BOARD_ID == BOARD_DEPLOY)

#define LED_STATUS_PIN GPIO_NUM_25
#define LED_INVERSE_MODE true

#endif

#if (BOARD_ID == BOARD_DEVELOP_01)

#define LED_STATUS_PIN GPIO_NUM_25
#define LED_INVERSE_MODE false

#endif
