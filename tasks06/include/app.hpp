#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Arduino.h>
#include "esp_log.h"
#include "system_constants.hpp"
#include "board.hpp"
#include "system_tasks.hpp"
#include "ble_handler.hpp"
#include "button_handler.hpp"
#include "led_handler.hpp"

class App
{
public:
    static void start();
    static void haltSystem();
    static void factoryReset();
    static void remoteReset();

    static void startBleInterface();

    static void disableProcessing();
    static void enableProcessing();
    static boolean checkProcessing();

    static void initTasks();

private:
    static boolean enableProcessing_;
};
