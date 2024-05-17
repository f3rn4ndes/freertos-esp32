#pragma once

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system_constants.hpp"
#include "esp_log.h"
#include <queue>
#include <string>

    class BLEHandler
{
public:
    BLEHandler();
    ~BLEHandler();

    void initBLE(const std::string &deviceName);
    void startAdvertising();
    void sendData(const std::string &data);
    std::string receiveData();

    static void handleReceivedData(void *pvParameter);
    static void handleSendingData(void *pvParameter);
    static void handleDisconnection(void *pvParameter);

    bool deviceConnected;
    std::queue<std::string> receiveQueue;

private:
    BLEServer *pServer;
    BLEService *pService;
    BLECharacteristic *pTxCharacteristic;
    BLECharacteristic *pRxCharacteristic;
    std::queue<std::string> sendQueue;

    static BLEHandler *instance;

    bool oldDeviceConnected;
    uint32_t reconnectDelay;

    void attemptReconnection();
};
