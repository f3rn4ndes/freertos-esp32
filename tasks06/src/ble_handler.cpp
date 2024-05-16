#include "ble_handler.hpp"

void BleHandler::init(void)
{
    // Create the BLE Device
    BLEDevice::init(kBleHandlerDeviceName); // Give it a name

    // Create a BLE Server
    pServer = BLEDevice::createServer();

    pServer->setCallbacks(new MyServerCallbacks());

    // Create a UART service
    pService = pServer->createService(kBleHandlerServiceUuid);

    // Cria uma Característica BLE para envio dos dados
    pCharacteristic = pService->createCharacteristic(
        kBleHandlerDhtDataCharUuid,
        BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristic->addDescriptor(new BLE2902());

    // cria uma característica BLE para recebimento dos dados
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        kBleHandlerCharacteristicUuidRx,
        BLECharacteristic::PROPERTY_WRITE);

    // Set Callbacks
    pCharacteristic->setCallbacks(new CharacteristicCallbacks());

    // Start Service
    pService->start();

    // Start Advertisement
    pServer->getAdvertising()->start();
}