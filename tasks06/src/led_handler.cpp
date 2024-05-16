#include "led_handler.hpp"

LedHandler ledStatus(LED_STATUS_PIN);

LedHandler::LedHandler(uint8_t pin)
{
    BaseType_t rc;

    pin_ = pin;
    type_ = LedType::TYPE_SOLID;
    active_ = false;
    mode_ = kLedOff;
    inverseLogic_ = kledInverse;
    taskHandle_ = NULL;

    pinMode(pin_, OUTPUT);

    rc = xTaskCreatePinnedToCore(
        this->taskWrapper,
        "LED_TASK",
        LED_TASK_STACK_SIZE,
        this,
        LED_TASK_PRIORITY,
        &taskHandle_,
        LED_TASK_CORE);
    assert(rc == pdPASS);
}

LedHandler::~LedHandler()
{
    vTaskDelete(taskHandle_);
}

void LedHandler::setLedType(LedType new_type)
{
    type_ = new_type;
    setActive(false);
    setMode(kLedOff);
}

LedHandler::LedType LedHandler::getLedType()
{
    return type_;
}

void LedHandler::setActive(boolean new_active)
{
    active_ = new_active;
}

boolean LedHandler::getActive()
{
    return active_;
}

void LedHandler::setMode(uint8_t new_mode)
{
    mode_ = new_mode;
}

uint8_t LedHandler::getMode()
{
    return mode_;
}

void LedHandler::setInverseLogic(boolean logic)
{
    inverseLogic_ = logic;
}

boolean LedHandler::getInverseLogic()
{
    return inverseLogic_;
}

void LedHandler::taskWrapper(void *pvParameters)
{
    LedHandler *ledHandler = static_cast<LedHandler *>(pvParameters);
    ledHandler->executeTask();
}

void LedHandler::toogleActive()
{
    active_ = (active_ ? false : true);
}

void LedHandler::executeTask()
{
    uint8_t real_mode;

    for (;;)
    {
        real_mode = getMode();

        if (!active_)
            real_mode = kLedOff;

        if (getInverseLogic())
        {
            real_mode = kLedOn - real_mode;
        }

        switch (type_)
        {
        case LedType::TYPE_SOLID:
            digitalWrite(pin_, real_mode ? HIGH : LOW);
            vTaskDelay((LED_TASK_DELAY_MS) / portTICK_PERIOD_MS);
            break;
        case LedType::TYPE_BLINK_SLOW:
            digitalWrite(pin_, real_mode ? HIGH : LOW);
            setMode(kLedOn - getMode());
            vTaskDelay((LED_TASK_DELAY_MS * LED_TASK_DELAY_MS_FACTOR) / portTICK_PERIOD_MS);
            break;
        case LedType::TYPE_BLINK_FAST:
            digitalWrite(pin_, real_mode ? HIGH : LOW);
            setMode(kLedOn - getMode());
            vTaskDelay((LED_TASK_DELAY_MS) / portTICK_PERIOD_MS);
            break;
        }
    }
}
