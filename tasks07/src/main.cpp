#include <Arduino.h>
#include "system_constants.hpp"
#include "esp_log.h"

void setup()
{
  delay(kInitialDelay);
  Serial.begin(kSerialBaudRate);
  Serial.setDebugOutput(kAppLogMessages);
  ESP_LOGV(kMainLogTag, "Starting Application....");
  Serial.println("(P) Starting Application....");
}

void loop()
{
  static int counter = 5;
  // put your main code here, to run repeatedly:
  ESP_LOGW(kMainLogTag, "Testing ESP32-S3-WROOM-1....");
  Serial.println("(P) Testing ESP32-S3-WROOM-1....");
  delay(kPrintDelayMs);
  if (counter)
  {
    counter--;
    if (!counter)
      Serial.setDebugOutput(false);
  }
}
