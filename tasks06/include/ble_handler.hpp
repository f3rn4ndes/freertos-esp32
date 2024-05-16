#pragma once

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "system_constants.hpp"

class BleHandler
{
public:
    BleHandler(uint8_t pin);
    ~BleHandler();
    void init();
    void processingIncomingData();
    void sendData();

private:
    TaskHandle_t taskHandle_;
    BLEServer *pServer_ = NULL;
    BLEService *pService_ = NULL;
    BLECharacteristic *pCharacteristic_ = NULL;
};

/**
 * @brief BLE Classes and Methods
 *
 */
class MyServerCallbacks : public BLEServerCallbacks
{

    /*
    In BLE, the amount of data you can send in a single packet is determined by
    the Maximum Transmission Unit (MTU) size. By default, the BLE specification
     sets an MTU size of 23 bytes. After accounting for the 3-byte header,
     4-byte MIC (if encryption is enabled), and 4-byte L2CAP header,
     you're left with 20 bytes for the ATT payload. If you're seeing a limit of
     12 characters, it's possible that there are additional headers
     or structures in your specific implementation
    */

    // void onConnect(BLEServer *pServer)
    void onConnect(BLEServer *pServer, esp_ble_gatts_cb_param_t *param) // new method to set MTU
    {
        uint16_t _connId;
        Serial.printf("[INFO] Client Connected!\n");
        // Serial.printf("[INFO] Current BLEDevice MTU Size : %d\n", BLEDevice::getMTU());
        device.connected = true;
        // Change MTU
        // BLEDevice::setMTU(BLE_MTU_SIZE);
        // _connId = param->connect.conn_id;               // Get the connection ID from the callback parameter
        // pSServer->updatePeerMTU(BLE_MTU_SIZE, _connId); // Request a MTU siz for this connection

        BLEDevice::startAdvertising();
        // Serial.printf("[INFO] New BLEDevice MTU Size : %d\n", BLEDevice::getMTU());
    }

    void onDisconnect(BLEServer *pServer)
    {
        Serial.printf("[INFO] Client Disconnected!\n");
        device.connected = false;
    }
};

class CharacteristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *characteristic)
    {
        unsigned int _counter;

        // point to characteristic value
        std::string _rxMessage = characteristic->getValue();
        // check if received value has length greater than zero
        if (_rxMessage.length() > 0)
        {
            unsigned int _length = _rxMessage.length();
            Serial.printf("[INFO] Received message: ");
            for (_counter = 0; _counter < _length; _counter++)
            {
                Serial.printf("%02X ", _rxMessage[_counter]);
            }
            Serial.println();

            deviceProcessIncomingData(_rxMessage);
        }
        std::string rxHora = characteristic->getValue();
        if (rxHora.length() > 0)
        {
            int32_t unixTime = strtol(rxHora.c_str(), nullptr, 10);
            unixTime -= 3 * 3600; // Subtract 3 hours
            timeval epoch = {
                unixTime,
            };
            settimeofday((const timeval *)&epoch, nullptr);
        }
    }
};
