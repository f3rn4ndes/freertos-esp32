#include "ble_handler.hpp"
#include "ble_server_callbacks.hpp"
#include "ble_characteristic_callbacks.hpp"
#include "system_constants.hpp"

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

BLEHandler *BLEHandler::instance = nullptr;

BLEHandler::BLEHandler()
{
    instance = this;
    pServer = nullptr;
    pService = nullptr;
    pTxCharacteristic = nullptr;
    pRxCharacteristic = nullptr;
    deviceConnected = false;
    oldDeviceConnected = false;
    reconnectDelay = 5000; // Reconnect after 5 seconds
}

BLEHandler::~BLEHandler()
{
    // Cleanup if necessary
}

void BLEHandler::initBLE(const std::string &deviceName)
{
    BLEDevice::init(deviceName);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyBLEServerCallbacks(this));
    pService = pServer->createService(SERVICE_UUID);

    pTxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY);
    pTxCharacteristic->addDescriptor(new BLE2902());

    pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE);
    pRxCharacteristic->setCallbacks(new MyBLECharacteristicCallbacks(this));

    pService->start();
    startAdvertising();

    // Create FreeRTOS tasks for handling data and disconnections
    xTaskCreate(handleReceivedData, "handleReceivedData", 2048, this, 1, nullptr);
    xTaskCreate(handleSendingData, "handleSendingData", 2048, this, 1, nullptr);
    xTaskCreate(handleDisconnection, "handleDisconnection", 2048, this, 1, nullptr);
}

void BLEHandler::startAdvertising()
{
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}

void BLEHandler::sendData(const std::string &data)
{
    sendQueue.push(data);
}

std::string BLEHandler::receiveData()
{
    if (!receiveQueue.empty())
    {
        std::string data = receiveQueue.front();
        receiveQueue.pop();
        return data;
    }
    return "";
}

void BLEHandler::handleReceivedData(void *pvParameter)
{
    BLEHandler *handler = static_cast<BLEHandler *>(pvParameter);
    while (true)
    {
        if (handler->pRxCharacteristic->getValue().length() > 0)
        {
            std::string receivedData = handler->pRxCharacteristic->getValue();
            handler->receiveQueue.push(receivedData);
            handler->pRxCharacteristic->setValue(""); // Clear the value after reading
        }
        vTaskDelay(pdMS_TO_TICKS(kBLEDelaymsShort)); // Check every 100ms
    }
}

void BLEHandler::handleSendingData(void *pvParameter)
{
    BLEHandler *handler = static_cast<BLEHandler *>(pvParameter);
    while (true)
    {
        if (!handler->sendQueue.empty())
        {
            std::string dataToSend = handler->sendQueue.front();
            handler->sendQueue.pop();
            handler->pTxCharacteristic->setValue(dataToSend);
            handler->pTxCharacteristic->notify();
        }
        vTaskDelay(pdMS_TO_TICKS(kBLEDelaymsShort)); // Send data every 100ms if available
    }
}

void BLEHandler::handleDisconnection(void *pvParameter)
{
    BLEHandler *handler = static_cast<BLEHandler *>(pvParameter);
    while (true)
    {
        if (!handler->deviceConnected && handler->oldDeviceConnected)
        {
            handler->attemptReconnection();
        }
        handler->oldDeviceConnected = handler->deviceConnected;
        vTaskDelay(pdMS_TO_TICKS(kBLEDelaymsLong)); // Check connection status every second
    }
}

void BLEHandler::attemptReconnection()
{
    BLEDevice::startAdvertising();
    vTaskDelay(pdMS_TO_TICKS(reconnectDelay)); // Wait for the specified reconnect delay
}
