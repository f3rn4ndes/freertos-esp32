#include "ble_characteristic_callbacks.hpp"
#include "ble_handler.hpp"

MyBLECharacteristicCallbacks::MyBLECharacteristicCallbacks(BLEHandler *handler) : handler(handler) {}

void MyBLECharacteristicCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
    if (handler)
    {
        std::string receivedData = pCharacteristic->getValue();
        handler->receiveQueue.push(receivedData);
    }
    else
    {
        ESP_LOGE(kBLEHandlerLogTag, "Failed Event OnWrite - No Handler");
    }
}
