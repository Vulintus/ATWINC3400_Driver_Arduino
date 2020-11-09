#ifndef VULINTUS_ARDUINO_BLE_TYPED_CHARACTERISTIC_H
#define VULINTUS_ARDUINO_BLE_TYPED_CHARACTERISTIC_H

#include "vulintus_arduino_ble/BLECharacteristic.h"

namespace VulintusArduinoBLE
{
    template<typename T> class BLETypedCharacteristic : public BLECharacteristic
    {
        public:
            BLETypedCharacteristic(const char* uuid, unsigned char properties);

            int writeValue(T value);
            int setValue(T value) { return writeValue(value); }
            T value(void);

            int writeValueLE(T value);
            int setValueLE(T value) { return writeValueLE(value); }
            T valueLE(void);

            int writeValueBE(T value);
            int setValueBE(T value) { return writeValueBE(value); }
            T valueBE(void);

        private:
            T byteSwap(T value);
    };

    template<typename T> BLETypedCharacteristic<T>::BLETypedCharacteristic(const char* uuid, unsigned char properties) :
        BLECharacteristic(uuid, properties, sizeof(T), true)
    {
        T value;
        memset(&value, 0x00, sizeof(value));
        writeValue(value);
    }

    template<typename T> int BLETypedCharacteristic<T>::writeValue(T value)
    {
        return BLECharacteristic::writeValue((uint8_t*)&value, sizeof(T));
    }

    template<typename T> T BLETypedCharacteristic<T>::value()
    {
        T value;
        memcpy(&value, (unsigned char*)BLECharacteristic::value(), BLECharacteristic::valueSize());
        return value;
    }

    template<typename T> int BLETypedCharacteristic<T>::writeValueLE(T value)
    {
        return writeValue(value);
    }

    template<typename T> T BLETypedCharacteristic<T>::valueLE()
    {
        return value();
    }

    template<typename T> int BLETypedCharacteristic<T>::writeValueBE(T value)
    {
        return writeValue(byteSwap(value));
    }

    template<typename T> T BLETypedCharacteristic<T>::valueBE()
    {
        return byteSwap(value());
    }

    template<typename T> T BLETypedCharacteristic<T>::byteSwap(T value)
    {
        T result;
        unsigned char* src = (unsigned char*)&value;
        unsigned char* dst = (unsigned char*)&result;

        for (int i = 0; i < sizeof(T); i++) 
        {
            dst[i] = src[sizeof(T) - i - 1];
        }

        return result;
    }
}

#endif /* VULINTUS_ARDUINO_BLE_TYPED_CHARACTERISTIC_H */
