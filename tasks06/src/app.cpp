#include "app.hpp"
#include <Arduino.h>

App::App(BLEHandler *bleHandler)
    : bleHandler(bleHandler), sendingTaskHandle(nullptr), isSending(false), sendInterval(2000)
{ // Send every 2 seconds
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
        xTaskCreate(sendingTask, "sendingTask", 2048, this, 1, &sendingTaskHandle); // Reduce stack size to 2048
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
    while (app->isSending)
    {
        app->bleHandler->sendData("Hello from ESP32!\n");
        vTaskDelay(pdMS_TO_TICKS(app->sendInterval));
    }
}
