#pragma once

// Includes
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtostasktemplate.h"
#include "systemtasks.h"
#include "board.h"
#include "led.h"
#include "verbose.h"
#include "sysclock.h"
#include "observertemplate.h"
#include "systemtypes.h"

// Defines
#define BUTTON_F1 (uint8_t) BOARD_BUTTON_F1_PIN
#define BUTTON_F2 (uint8_t) BOARD_BUTTON_F2_PIN
#define BUTTON_F3 (uint8_t) BOARD_BUTTON_F3_PIN

// External Objects
extern LedTask ledF1;
extern LedTask ledF2;
extern VerboseTask verbose;

// Data Types - typedefs, structs, unions and/or enumerated

typedef struct
{
    uint8_t pin;
    ButtonFunction_t function;
} Button_t;

// Classes
class ButtonTask : public RTOSTaskTemplate<Button_t>, public Subject
{
public:
    void setup(Button_t &pParameters) override
    {
        mButton = pParameters;
        pinMode(mButton.pin, INPUT_PULLUP);
        mPressed = false;
    }

private:
    Button_t mButton;

    uint8_t mPressed = false;

protected:
    void execute() override
    {
        // check pressed
        if (!digitalRead(mButton.pin) && !mPressed)
        {
            action();
            mPressed = true;
        }

        // check released
        if (digitalRead(mButton.pin) && mPressed)
        {
            mPressed = false;
        }
    }

    void action()
    {
        VERBOSE((String) "Task: " + getTaskName() + " - Button Pressed", VERBOSE_TASK_BUTTON);
        notify((uint8_t)mButton.function);
    }
};

// Public Functions
void buttonSetup(void);
void buttonInit(void);
