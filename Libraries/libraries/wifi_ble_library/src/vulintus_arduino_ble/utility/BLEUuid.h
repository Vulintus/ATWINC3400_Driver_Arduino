#ifndef VULINTUS_ARDUINO_BLE_UUID_H
#define VULINTUS_ARDUINO_BLE_UUID_H

#include <Arduino.h>

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

#define BLE_UUID_MAX_LENGTH 16

namespace VulintusArduinoBLE
{
    /// <summary>
    /// A UUID is an abbreviation you will see a lot in the BLE world. 
    /// It is a unique number used to identify services, characteristics and 
    /// descriptors, also known as attributes. These IDs are transmitted over 
    /// the air so that e.g. a peripheral can inform a central what services it provides.
    ///
    /// There are two kinds of UUIDs. The first type is a short 16-bit UUID. These are 
    /// pre-defined services and characteristics. The second is a longer 128-bit UUID.
    /// These are vendor specific UUIDs. This is the type of UUID you need to use when 
    /// you are making your own custom services and characteristics.
    ///
    /// Source: https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/ble-services-a-beginners-tutorial
    /// </summary>
    class BLEUuid
    {
        public:
            BLEUuid(const char * str);

            const char* str() const;
            const uint8_t * data() const;
            uint8_t length() const;

            static const char* uuidToString(const uint8_t* data, uint8_t length);
        private:
            const char* _str;
            uint8_t     _data[BLE_UUID_MAX_LENGTH];
            uint8_t     _length;

        private:
            at_ble_uuid_t _at_ble_uuid;
    };
}



#endif /* VULINTUS_ARDUINO_BLE_UUID_H */
