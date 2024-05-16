#pragma once

#include <string>
#include <iostream>
#include <Arduino.h>
#include "board.hpp"

// App
static const boolean kAppLogMessages = true;

static const uint32_t kAppSerialBaudRate = 115200;
static const uint32_t kAppStartDelay = 1000; // ms
static const char *kAppSeparatorLine = "\n--------------------------------------------------------------------";

static const boolean kAppParseTest = false;

static const uint8_t kAppMaxNumOfTasks = 8; // check

// Log Tags
static const char *kMainLogTag = "Main";
static const char *kAppLogTag = "App";

static const char *kBleHandlerLogTag = "BLE Handler";
static const char *kButtonHandleLogTag = "Button Handler";
static const char *kLedHandleLogTag = "Led Handler";

// Button
static const uint32_t kDebounceTime = 100;   // ms
static const uint32_t kLongPressTime = 2000; // ms

// Led
static const uint8_t kLedOff = 0;
static const uint8_t kLedOn = 1;
static const boolean kledInverse = LED_INVERSE_MODE;

// BLE Handler
static const char *kBleHandlerServiceUuid = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
static const char *kBleHandlerCharacteristicUuidRx = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
static const char *kBleHandlerDhtDataCharUuid = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E";
static const char *kBleHandlerDeviceName = "MY_BLE_DEVICE";
static const uint32_t kBleHandlerMtuSize = 100;
