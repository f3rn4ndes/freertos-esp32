#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Arduino.h>
#include "esp_log.h"
#include "board.hpp"
#include "system_constants.hpp"
#include "system_tasks.hpp"

class LedHandler
{
public:
    enum class LedType
    {
        TYPE_SOLID,
        TYPE_BLINK_SLOW,
        TYPE_BLINK_FAST
    };

    LedHandler(uint8_t pin);
    ~LedHandler();

    static void taskWrapper(void *pvParameters);

    void setLedType(LedType new_type);
    LedType getLedType();

    void setMode(uint8_t new_mode);
    uint8_t getMode();

    void setActive(boolean new_active);
    boolean getActive();

    void toogleActive();

    void setInverseLogic(boolean new_logic);
    boolean getInverseLogic();

private:
    uint8_t pin_;
    LedType type_;
    uint8_t active_;
    uint8_t mode_;
    boolean inverseLogic_;
    TaskHandle_t taskHandle_;
    void executeTask();
};

extern LedHandler ledStatus;
