#include "button_handler.hpp"

ButtonHandler testButton(TEST_BUTTON_PIN);

ButtonHandler::ButtonHandler(uint8_t pin)
{
    BaseType_t rc;

    pin_ = pin;
    buttonPressed_ = false;
    longPress_ = false;
    lastPressTime_ = 0;
    taskHandle_ = NULL;

    pinMode(pin_, INPUT_PULLUP);

    rc = xTaskCreatePinnedToCore(
        this->taskWrapper,
        "BUTTON_TASK",
        BUTTON_TASK_STACK_SIZE,
        this,
        BUTTON_TASK_PRIORITY,
        &taskHandle_,
        BUTTON_TASK_CORE);
    assert(rc == pdPASS);

    ESP_LOGI(kButtonHandleLogTag, "Button task create\n");
}

ButtonHandler::~ButtonHandler()
{
    vTaskDelete(taskHandle_);
}

void ButtonHandler::taskWrapper(void *pvParameters)
{
    ButtonHandler *buttonHandler = static_cast<ButtonHandler *>(pvParameters);
    buttonHandler->executeTask();
}

void ButtonHandler::executeTask()
{
    for (;;)
    {
        if (!digitalRead(pin_))
        {
            if (!buttonPressed_)
            {
                lastPressTime_ = millis();
                buttonPressed_ = true;
            }

            if (!longPress_ && buttonPressed_ && (millis() - lastPressTime_) > kLongPressTime)
            {
                longPressAction();
                longPress_ = true;
            }
        }
        else
        {
            if (!longPress_ && buttonPressed_ && (millis() - lastPressTime_) > kDebounceTime)
            {
                shortPressAction();
            }
            longPress_ = false;
            buttonPressed_ = false;
            lastPressTime_ = 0;
        }
        vTaskDelay(BUTTON_TASK_DELAY_MS / portTICK_PERIOD_MS);
    }
}

void ButtonHandler::shortPressAction()
{
    ESP_LOGI(kButtonHandleLogTag, "Short Press Action\n");
    App::disableProcessing();
}

void ButtonHandler::longPressAction()
{
    ESP_LOGI(kButtonHandleLogTag, "Long Press Action\n");
    App::enableProcessing();
}
