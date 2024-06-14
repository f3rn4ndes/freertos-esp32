#include "app.hpp"
#include <Arduino.h>

App::App(BLEHandler *bleHandler)
    : bleHandler(bleHandler), sendingTaskHandle(nullptr), isSending(false), sendInterval(kBLESendIntervalMs),
      countDown(kCountDown)
{
}

void App::handleCommand(const std::string &command)
{

    std::string _message = "";

    ESP_LOGI(kAppLogTag, "Received Command: %s", command.c_str());

    for (int i = 0; i < command.length(); i++)
    {
        if (command[i] != '\n' && command[i] != '\r')
        {
            _message += command[i];
        }
    }

    if (_message == "START")
    {
        ESP_LOGI(kAppLogTag, "START Command Received");
        startSendingTask();
    }
    else if (_message == "STOP")
    {
        ESP_LOGI(kAppLogTag, "STOP Command Received");
        stopSendingTask();
    }
    else
    {
        // Handle other commands
    }
}

void App::startSendingTask()
{
    if (!isSending)
    {
        isSending = true;
        xTaskCreate(sendingTask, "sendingTask", kBLEHandlerStackDepthSize, this, 1, &sendingTaskHandle);
    }
}

void App::stopSendingTask()
{
    if (isSending)
    {
        isSending = false;
        if (sendingTaskHandle != nullptr)
        {
            vTaskDelete(sendingTaskHandle);
            sendingTaskHandle = nullptr;
        }
    }
}

void App::sendingTask(void *pvParameter)
{
    App *app = static_cast<App *>(pvParameter);
    uint32_t counter = app->countDown;
    while (app->isSending)
    {
        if (counter)
        {
            app->bleHandler->sendData("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz123456789012345678901234\r");
            counter--;
            if (!counter)
            {
                app->bleHandler->sendData("----------------\r");
                ESP_LOGI(kAppLogTag, "STOP Command Received");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(app->sendInterval));
    }
}
