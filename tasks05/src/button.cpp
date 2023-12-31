#include "button.h"

// Objects
ButtonTask buttonF1;
ButtonTask buttonF2;
ButtonTask buttonF3;

// Functions
void buttonSetup(void)
{
    Button_t _button;

    VERBOSE((String) "Function: " + __func__, VERBOSE_MODULE_BUTTON);

    _button.pin = BUTTON_F1;
    _button.function = bfChangeStatus;

    buttonF1.setup(_button);

    _button.pin = BUTTON_F2;
    _button.function = bfChangeStatus;

    buttonF2.setup(_button);

    _button.pin = BUTTON_F3;
    _button.function = bfInitStatus;

    buttonF3.setup(_button);

    buttonF1.attach(&ledF1); // led 1 vai ser notificado pelo botao 1

    buttonF2.attach(&ledF2);

    buttonF3.attach(&ledF1);
    buttonF3.attach(&ledF2);
}

void buttonInit(void)
{

    VERBOSE((String) "Function: " + __func__, VERBOSE_MODULE_BUTTON);

    buttonF1.createTask(
        "BUTTON F1",
        BUTTON_F1_TASK_STACK_SIZE,
        BUTTON_F1_TASK_PRIORITY,
        BUTTON_F1_TASK_CORE,
        SYSTEM_TASK_LOOP,
        BUTTON_F1_TASK_DELAY_MS);

    buttonF2.createTask(
        "BUTTON F2",
        BUTTON_F2_TASK_STACK_SIZE,
        BUTTON_F2_TASK_PRIORITY,
        BUTTON_F2_TASK_CORE,
        SYSTEM_TASK_LOOP,
        BUTTON_F2_TASK_DELAY_MS);

    buttonF3.createTask(
        "BUTTON F3",
        BUTTON_F3_TASK_STACK_SIZE,
        BUTTON_F3_TASK_PRIORITY,
        BUTTON_F3_TASK_CORE,
        SYSTEM_TASK_LOOP,
        BUTTON_F3_TASK_DELAY_MS);
}
