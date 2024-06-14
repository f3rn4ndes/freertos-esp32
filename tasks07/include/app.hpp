#pragma once

#include "ble_handler.hpp"
#include "esp_log.h"
#include "system_constants.hpp"

class App
{
public:
    App(BLEHandler *bleHandler);
    void handleCommand(const std::string &command);
    void startSendingTask();
    void stopSendingTask();

    static void sendingTask(void *pvParameter);

private:
    BLEHandler *bleHandler;
    TaskHandle_t sendingTaskHandle;
    bool isSending;
    uint32_t sendInterval;
    uint32_t countDown;
};
