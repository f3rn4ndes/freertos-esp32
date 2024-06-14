#include "main.hpp"

BLEHandler bleHandler;
App app(&bleHandler);

void setup()
{
  delay(kAppStartDelay);
  Serial.begin(kAppSerialBaudRate);
  Serial.setDebugOutput(kAppLogMessages);
  bleHandler.initBLE(kBLEHandlerDeviceName);
  ESP_LOGI(kMainLogTag, "Application Start \n");
}

void loop()
{
  if (bleHandler.deviceConnected)
  {
    std::string receivedData = bleHandler.receiveData();
    if (!receivedData.empty())
    {
      app.handleCommand(receivedData);
    }
  }
  delay(kAppLoopDelay); // Add a small delay to avoid busy looping
}
