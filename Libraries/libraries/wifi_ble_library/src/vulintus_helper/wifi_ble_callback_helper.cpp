#include "WiFi101.h"
#include "ArduinoBLE.h"

extern WiFiClass WiFi;
extern VulintusArduinoBLE::BLELocalDevice BLE;

void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
    WiFi.handleEvent(u8MsgType, pvMsg);
}