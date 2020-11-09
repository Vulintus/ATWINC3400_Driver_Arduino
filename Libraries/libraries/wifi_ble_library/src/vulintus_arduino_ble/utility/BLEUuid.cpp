#include <stdlib.h>
#include <string.h>

#include "vulintus_arduino_ble/utility/BLEUuid.h"

namespace VulintusArduinoBLE
{
    BLEUuid::BLEUuid(const char * str) 
        : _str(str)
    {
        char temp[] = {0, 0, 0};

        memset(_data, 0x00, sizeof(_data));

        _length = 0;
        for (int i = strlen(str) - 1; i >= 0 && _length < BLE_UUID_MAX_LENGTH; i -= 2) 
        {
            if (str[i] == '-') 
            {
                i++;
                continue;
            }

            temp[0] = str[i - 1];
            temp[1] = str[i];

            _data[_length] = strtoul(temp, NULL, 16);

            _length++;
        }

        if (_length <= 2) 
        {
            _length = 2;
        } 
        else 
        {
            _length = 16;
        }

        //Set the _at_ble_uuid variable
        memcpy(_at_ble_uuid.uuid, _data, BLE_UUID_MAX_LENGTH);
        if (_length <= 2)
        {
            _at_ble_uuid.type = at_ble_uuid_type_t::AT_BLE_UUID_16;
        }
        else
        {
            _at_ble_uuid.type = at_ble_uuid_type_t::AT_BLE_UUID_128;
        }
    }

    const char* BLEUuid::str() const
    {
        return _str;
    }

    const uint8_t* BLEUuid::data() const
    {
        return _data;
    }

    uint8_t BLEUuid::length() const
    {
        return _length;
    }

    const char* BLEUuid::uuidToString(const uint8_t* data, uint8_t length)
    {
        static char uuid[36 + 1];
        char* c = uuid;

        for (int i = length - 1; i >= 0; i--) 
        {
            uint8_t b = data[i];

            utoa(b >> 4, c++, 16);
            utoa(b & 0x0f, c++, 16);

            if (i == 6 || i == 8 || i == 10 || i == 12) 
            {
                *c++ = '-';
            }
        }

        *c = '\0';

        return uuid;
    }
}

