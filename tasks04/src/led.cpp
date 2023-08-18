#include "led.h"

// Objects
LedTask ledF1;
LedTask ledF2;

// Functions

void ledSetup(void)
{
    Led_t _leds;

    _leds.pin = LED_F1;
    _leds.mode = lmClear;

    ledF1.setup(_leds);

    _leds.pin = LED_F2;
    _leds.mode = lmClear;

    ledF2.setup(_leds);
}

void ledInit(void)
{
    ledF1.createTask("Led F1", LED_F1_TASK_STACK_SIZE, LED_F1_TASK_PRIORITY, LED_F1_TASK_CORE, false, 0);
    ledF2.createTask("Led F2", LED_F2_TASK_STACK_SIZE, LED_F2_TASK_PRIORITY, LED_F2_TASK_CORE, false, 0);
}
