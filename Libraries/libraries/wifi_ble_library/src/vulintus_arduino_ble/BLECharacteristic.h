#ifndef __VULINTUS_ARDUINO_BLE_CHARACTERISTIC_H
#define __VULINTUS_ARDUINO_BLE_CHARACTERISTIC_H

#include "vulintus_arduino_ble/BLEUuid.h"

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

namespace VulintusArduinoBLE
{
    class BLECharacteristic
    {
        public:

            //Constructors
            BLECharacteristic ();
            BLECharacteristic(const char* uuid, uint8_t properties, int valueSize, bool fixedLength = false);
            BLECharacteristic(const char* uuid, uint8_t properties, const char* value);

            //Destructor
            virtual ~BLECharacteristic ();

            const char* uuid() const;
            at_ble_handle_t GetCharacteristicValueHandle ();

            uint8_t properties() const;
            void broadcast ();

            int valueSize() const;
            const uint8_t* value() const;
            int readValue();
            
            int writeValue(const uint8_t value[], int length);
            int writeValue(const void* value, int length);
            int writeValue(const char* value);
            int writeValue(uint8_t value);
            int writeValue(int8_t value);
            int writeValue(uint16_t value);
            int writeValue(int16_t value);
            int writeValue(uint32_t value);
            int writeValue(int32_t value);            

        protected:
            friend class BLELocalDevice;
            friend class BLEService;

            BLEUuid characteristic_uuid;
            uint8_t* characteristic_value;
            uint16_t characteristic_value_size;
            bool is_fixed_length;
            bool should_broadcast;

            at_ble_characteristic_t internal_characteristic;
    };
}

#endif /* __VULINTUS_ARDUINO_BLE_CHARACTERISTIC_H */