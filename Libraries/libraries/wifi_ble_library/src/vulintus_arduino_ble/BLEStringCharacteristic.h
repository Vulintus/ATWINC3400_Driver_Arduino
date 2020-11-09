#ifndef VULINTUS_ARDUINO_BLE_STRING_CHARACTERISTIC_H
#define VULINTUS_ARDUINO_BLE_STRING_CHARACTERISTIC_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLECharacteristic.h"

namespace VulintusArduinoBLE
{
    class BLEStringCharacteristic : public BLECharacteristic
    {
        public:
            BLEStringCharacteristic(const char* uuid, unsigned char properties, int valueSize);

            int writeValue(const String& value);
            int setValue(const String& value) { return writeValue(value); }
            String value(void);

        private:
    };
}

#endif /* VULINTUS_ARDUINO_BLE_STRING_CHARACTERISTIC_H */
