#include <Arduino.h>
#include "system_constants.hpp"
#include "esp_log.h"

void setup()
{
  delay(kInitialDelay);
  Serial.begin(kSerialBaudRate);
  Serial.setDebugOutput(kAppLogMessages);
  ESP_LOGI(kMainLogTag, "Starting Application....");
}

void loop()
{
  // put your main code here, to run repeatedly:

  ESP_LOGI(kMainLogTag, "Testing ESP32-S3-WROOM-1....");
  delay(kPrintDelayMs);
}
