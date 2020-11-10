#include "vulintus_arduino_ble/BLECharacteristic.h"
#include "vulintus_arduino_ble/BLEUuid.h"
#include "vulintus_arduino_ble/ATT.h"
#include "vulintus_arduino_ble/BLEProperty.h"

namespace VulintusArduinoBLE
{
    /// <summary>
    /// Empty default constructor
    /// </summary>
    BLECharacteristic::BLECharacteristic()
    {
        characteristic_value_size = 0;
        characteristic_value = NULL;
        internal_characteristic.init_value = NULL;
        is_fixed_length = false;
        should_broadcast = false;
    }

    BLECharacteristic::BLECharacteristic(const char* uuid, uint8_t properties, int valueSize, bool fixedLength)
    {
        characteristic_uuid = BLEUuid(uuid);
        is_fixed_length = fixedLength;
        should_broadcast = false;

        internal_characteristic.uuid = *characteristic_uuid.get();
        internal_characteristic.properties = (at_ble_char_properties_t) properties;
        internal_characteristic.value_init_len = (uint16_t) valueSize;
        internal_characteristic.value_max_len = (uint16_t) valueSize;
        internal_characteristic.init_value = (uint8_t *) malloc(valueSize);
        memset(internal_characteristic.init_value, 0, valueSize);

        characteristic_value_size = internal_characteristic.value_init_len;
        characteristic_value = (uint8_t *) malloc(valueSize);
        memset(characteristic_value, 0, valueSize);
    }

    BLECharacteristic::BLECharacteristic(const char* uuid, uint8_t properties, const char* value) :
        BLECharacteristic(uuid, properties, strlen(value))
    {
        memcpy(internal_characteristic.init_value, (uint8_t *) value, strlen(value));
        writeValue(value);
    }

    BLECharacteristic::~BLECharacteristic()
    {
        if (internal_characteristic.init_value)
        {
            free(internal_characteristic.init_value);
        }
    }

    const char* BLECharacteristic::uuid() const
    {
        return characteristic_uuid.str();
    }

    at_ble_handle_t BLECharacteristic::GetCharacteristicValueHandle ()
    {
        return internal_characteristic.char_val_handle;
    }

    uint8_t BLECharacteristic::properties() const
    {
        return ((uint8_t) internal_characteristic.properties);
    }

    void BLECharacteristic::broadcast ()
    {
        if (internal_characteristic.properties & BLEProperty::BLEBroadcast)
        {
            should_broadcast = true;
        }
        else
        {
            should_broadcast = false;
        }
    }

    int BLECharacteristic::valueSize() const
    {
        return ((int) characteristic_value_size);
    }

    const uint8_t* BLECharacteristic::value() const
    {
        return characteristic_value;
    }

    int BLECharacteristic::readValue()
    {
        uint16_t bytes_read = 0;

        at_ble_status_t status = at_ble_characteristic_value_get(
            internal_characteristic.char_val_handle,
            characteristic_value,
            &bytes_read);

        return status;
    }

    int BLECharacteristic::writeValue(const uint8_t value[], int length)
    {
        //Reset the memory being used to store the value
        memset(characteristic_value, 0, characteristic_value_size);

        //Determine how many bytes to fill with new data
        int len_to_write = min(length, internal_characteristic.value_max_len);
        if (is_fixed_length)
        {
            if (len_to_write > characteristic_value_size)
            {
                len_to_write = characteristic_value_size;
            }
        }

        //Store the new value internally within this class
        memcpy(characteristic_value, value, len_to_write);

        //Determine if the characteristic size has changed
        if (!is_fixed_length)
        {
            if (len_to_write != characteristic_value_size)
            {
                characteristic_value_size = len_to_write;
            }
        }

        //Pass the new value along to the BLE module
        at_ble_status_t status = at_ble_characteristic_value_set(
            internal_characteristic.char_val_handle,
            characteristic_value,
            characteristic_value_size);


        if (internal_characteristic.properties & BLEProperty::BLEIndicate) 
        {
            ATT.SendIndication(internal_characteristic.char_val_handle);
        } 
        else if (internal_characteristic.properties & BLEProperty::BLENotify) 
        {
            ATT.SendNotification(internal_characteristic.char_val_handle);
        }

        if (should_broadcast) 
        {
            //TO DO
        }

        return status;
    }

    int BLECharacteristic::writeValue(const char* value)
    {
        return writeValue((uint8_t*)value, strlen(value));
    }

    int BLECharacteristic::writeValue(const void* value, int length)
    {
        return writeValue((const uint8_t*)value, length);
    }

    int BLECharacteristic::writeValue(uint8_t value)
    {
        return writeValue((uint8_t*)&value, sizeof(value));
    }

    int BLECharacteristic::writeValue(int8_t value)
    {
        return writeValue((uint8_t*)&value, sizeof(value));
    }

    int BLECharacteristic::writeValue(uint16_t value)
    {
        return writeValue((uint8_t*)&value, sizeof(value));
    }

    int BLECharacteristic::writeValue(int16_t value)
    {
        return writeValue((uint8_t*)&value, sizeof(value));
    }

    int BLECharacteristic::writeValue(uint32_t value)
    {
        return writeValue((uint8_t*)&value, sizeof(value));
    }

    int BLECharacteristic::writeValue(int32_t value)
    {
        return writeValue((uint8_t*)&value, sizeof(value));
    }
}