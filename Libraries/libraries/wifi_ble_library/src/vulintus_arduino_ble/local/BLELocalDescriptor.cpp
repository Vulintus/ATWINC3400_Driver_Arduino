#include <Arduino.h>
#include "vulintus_arduino_ble/local/BLELocalDescriptor.h"

namespace VulintusArduinoBLE
{
    BLELocalDescriptor::BLELocalDescriptor(const char* uuid, const uint8_t value[], int valueSize) 
        : BLELocalAttribute(uuid),
        _value(value),
        _valueSize(min(valueSize, 512)),
        _handle(0x0000)
    {
        //empty
    }

    BLELocalDescriptor::BLELocalDescriptor(const char* uuid, const char* value) 
        : BLELocalDescriptor(uuid, (const uint8_t*)value, strlen(value))
    {
        //empty
    }

    BLELocalDescriptor::~BLELocalDescriptor()
    {
        //empty
    }

    enum BLEAttributeType BLELocalDescriptor::type() const
    {
        return BLETypeDescriptor;
    }

    int BLELocalDescriptor::valueSize() const
    {
        return _valueSize;
    }

    const uint8_t* BLELocalDescriptor::value() const
    {
        return _value;
    }

    uint8_t BLELocalDescriptor::operator[] (int offset) const
    {
        return _value[offset];
    }

    void BLELocalDescriptor::setHandle(uint16_t handle)
    {
        _handle = handle;
    }

    uint16_t BLELocalDescriptor::handle() const
    {
        return _handle;
    }
}