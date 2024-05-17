#pragma once

#include <BLEDevice.h>

class BLEHandler; // Forward declaration

class MyBLEServerCallbacks : public BLEServerCallbacks
{
public:
    MyBLEServerCallbacks(BLEHandler *handler);

    void onConnect(BLEServer *pServer) override;
    void onDisconnect(BLEServer *pServer) override;

private:
    BLEHandler *handler;
};

