#include "main.hpp"

BLEHandler bleHandler;
App app(&bleHandler);

void setup()
{
  delay(kAppStartDelay);
  Serial.begin(kAppSerialBaudRate);
  bleHandler.initBLE(kBLEHandlerDeviceName);
  Serial.printf("Application Start");
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
