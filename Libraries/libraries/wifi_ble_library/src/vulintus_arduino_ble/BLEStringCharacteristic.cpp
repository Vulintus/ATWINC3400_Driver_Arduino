#include "vulintus_arduino_ble/BLEStringCharacteristic.h"

namespace VulintusArduinoBLE
{
    BLEStringCharacteristic::BLEStringCharacteristic(const char* uuid, unsigned char properties, int valueSize) :
        BLECharacteristic(uuid, properties, valueSize)
    {
        //empty
    }

    int BLEStringCharacteristic::writeValue(const String& value)
    {
        return BLECharacteristic::writeValue(value.c_str());
    }

    String BLEStringCharacteristic::value(void)
    {
        String str;
        int length = BLECharacteristic::valueLength();
        const uint8_t* val = BLECharacteristic::value();

        str.reserve(length);

        for (int i = 0; i < length; i++) 
        {
            str += (char)val[i];
        }

        return str;
    }
}

