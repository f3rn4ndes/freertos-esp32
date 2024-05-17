#include "ble_server_callbacks.hpp"
#include "ble_handler.hpp"
#include "system_constants.hpp"

MyBLEServerCallbacks::MyBLEServerCallbacks(BLEHandler *handler) : handler(handler) {}

void MyBLEServerCallbacks::onConnect(BLEServer *pServer)
{
    if (handler)
    {
        handler->deviceConnected = true;
    }
    else
    {
        ESP_LOGE(kBLEHandlerLogTag, "Failed Event OnConnect - No Handler");
    }
}

void MyBLEServerCallbacks::onDisconnect(BLEServer *pServer)
{
    if (handler)
    {
        handler->deviceConnected = false;
    }
    else
    {
        ESP_LOGE(kBLEHandlerLogTag, "Failed Event OnDisconnect - No Handler");
    }
}
