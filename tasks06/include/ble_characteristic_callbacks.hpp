#pragma once

#include <BLEDevice.h>

class BLEHandler; // Forward declaration

class MyBLECharacteristicCallbacks : public BLECharacteristicCallbacks
{
public:
    MyBLECharacteristicCallbacks(BLEHandler *handler);

    void onWrite(BLECharacteristic *pCharacteristic) override;

private:
    BLEHandler *handler;
};

