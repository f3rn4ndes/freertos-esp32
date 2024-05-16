#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Arduino.h>
#include "esp_log.h"
#include "system_constants.hpp"
#include "board.hpp"
#include "system_tasks.hpp"
#include "app.hpp"

class ButtonHandler
{
public:
    ButtonHandler(uint8_t pin);
    ~ButtonHandler();
    static void taskWrapper(void *pvParameters);

private:
    uint8_t pin_;
    boolean buttonPressed_;
    boolean longPress_;
    unsigned long lastPressTime_;
    TaskHandle_t taskHandle_;

    void shortPressAction();
    void longPressAction();
    void executeTask();
};
