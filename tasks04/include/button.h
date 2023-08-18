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

// Defines
#define BUTTON_F1 (uint8_t) BOARD_BUTTON_F1_PIN
#define BUTTON_F2 (uint8_t) BOARD_BUTTON_F2_PIN
#define BUTTON_F3 (uint8_t) BOARD_BUTTON_F3_PIN

// External Objects
extern LedTask ledF1;
extern LedTask ledF2;
extern VerboseTask verbose;

// Data Types - typedefs, structs, unions and/or enumerated

typedef enum
{
    bfChangeLedF1 = 0,
    bfChangeLedF2,
    bfClearAll
} ButtonFunction_t;

typedef struct
{
    uint8_t pin;
    ButtonFunction_t function;
} Button_t;

// Classes
class ButtonTask : public RTOSTaskTemplate<Button_t>
{
public:
    void setup(Button_t &pParameters) override
    {
        mButton = pParameters;
        pinMode(mButton.pin, INPUT_PULLUP);
        mFree = true;
    }

private:
    Button_t mButton;

    uint8_t mFree = true;

protected:
    void execute() override
    {
        // check pressed
        if (!digitalRead(mButton.pin) && mFree)
        {
            mFree = false;
            action();
        }

        // check released
        if (digitalRead(mButton.pin) && !mFree)
        {
            mFree = true;
        }
    }

    void action()
    {
        VERBOSE((String) "Task: " + getTaskName() + " - Button Pressed", VERBOSE_TASK_BUTTON);

        switch (mButton.function)
        {
        case bfChangeLedF1:
            ledF1.changeMode();
            break;
        case bfChangeLedF2:
            ledF2.changeMode();
            break;
        case bfClearAll:
            ledF1.clear();
            ledF2.clear();
            break;
        }
    }
};

// Public Functions
void buttonSetup(void);
void buttonInit(void);
