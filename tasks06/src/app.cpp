#include "app.hpp"

boolean App::enableProcessing_ = false;

void App::start()
{

    disableProcessing();

    initTasks();

    delay(kAppStartDelay);

    ledStatus.setLedType(LedHandler::LedType::TYPE_BLINK_FAST);
    ledStatus.setActive(true);

    Serial.begin(kAppSerialBaudRate);
    delay(kAppStartDelay);

    Serial.setDebugOutput(kAppLogMessages);

    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);
    ESP_LOGI(kAppLogTag, "Device");
    ESP_LOGI(kAppLogTag, "Starting Application....");
    ESP_LOGI(kAppLogTag, "Checking System...");

    startBleInterface();

    ledStatus.setActive(false);
    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);
    ESP_LOGI(kAppLogTag, "Finish Boot....");
    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);

    enableProcessing();
}

void App::haltSystem()
{
    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);
    ledStatus.setLedType(LedHandler::LedType::TYPE_BLINK_FAST);
    ledStatus.setActive(true);
    while (true)
    {
        ESP_LOGE(kAppLogTag, "System Halt - Do Reset");
        vTaskDelay((LED_RESET_DELAY_MS) / portTICK_PERIOD_MS);
    }
}

void App::factoryReset()
{
    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);
    ledStatus.setLedType(LedHandler::LedType::TYPE_BLINK_SLOW);
    ledStatus.setActive(true);
    ESP_LOGI(kAppLogTag, "Factory Reset");
    // do something here...
    vTaskDelay((LED_RESET_DELAY_MS) / portTICK_PERIOD_MS);
    ESP.restart();
}

void App::remoteReset()
{
    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);
    ledStatus.setLedType(LedHandler::LedType::TYPE_BLINK_SLOW);
    ledStatus.setActive(true);
    ESP_LOGI(kAppLogTag, "Remote Reset");
    // do something here...
    vTaskDelay((LED_RESET_DELAY_MS) / portTICK_PERIOD_MS);
    ESP.restart();
}

void App::startBleInterface()
{
    ESP_LOGI(kAppLogTag, "%s", kAppSeparatorLine);
    ESP_LOGI(kAppLogTag, "[TEST] Ble Manager");
    // bleManager::start();
    ESP_LOGI(kAppLogTag, "[PASS] Ble Manager");
}

void App::disableProcessing()
{
    ESP_LOGI(kAppLogTag, "Disable Processing");
    ledStatus.setLedType(LedHandler::LedType::TYPE_BLINK_SLOW);
    ledStatus.setActive(true);
    enableProcessing_ = false;
}

void App::enableProcessing()
{
    ESP_LOGI(kAppLogTag, "Enable Processing");
    ledStatus.setLedType(LedHandler::LedType::TYPE_BLINK_FAST);
    ledStatus.setActive(true);
    enableProcessing_ = true;
}

boolean App::checkProcessing()
{
    return enableProcessing_;
}

void App::initTasks()
{
    // init other tasks here...
}
