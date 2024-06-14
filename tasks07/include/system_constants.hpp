#pragma once

#include <string>
#include <iostream>
#include <Arduino.h>

// App
static const boolean kAppLogMessages = false;

static const uint32_t kAppSerialBaudRate = 115200;
static const uint32_t kAppStartDelay = 1000; // ms
static const uint32_t kAppLoopDelay = 100;   // ms

static const uint32_t kBLEDelaymsShort = 4;   // ms
static const uint32_t kBLEDelaymsLong = 1000; // ms

static const char *kAppSeparatorLine = "\n--------------------------------------------------------------------";

static const boolean kAppParseTest = false;

static const uint8_t kAppMaxNumOfTasks = 8; // check

// Log Tags
static const char *kMainLogTag = "Main";
static const char *kAppLogTag = "App";

static const char *kBLEHandlerLogTag = "BLE Handler";

// BLE Handler
static const char *kBLEHandlerServiceUuid = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
static const char *kBLEHandlerCharacteristicUuid = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
static const char *kBLEHandlerDeviceName = "MY_BLE_DEVICE";
static const uint32_t kBleHandlerMtuSize = 100;

static const uint32_t kBLEHandlerStackDepthSize = 8192; // in Bytes

static const uint32_t kBLESendIntervalMs = 10; // in milisseconds
static const uint32_t kCountDown = 100;
