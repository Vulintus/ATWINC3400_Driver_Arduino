//#include "vulintus_arduino_ble/utility/ATT.h"
#include "vulintus_arduino_ble/remote/BLERemoteDescriptor.h"

namespace VulintusArduinoBLE
{
    BLERemoteDescriptor::BLERemoteDescriptor(const uint8_t uuid[], 
                                             uint8_t uuidLen, 
                                             uint16_t connectionHandle, 
                                             uint16_t handle) :
        BLERemoteAttribute(uuid, uuidLen),
        _connectionHandle(connectionHandle),
        _handle(handle),
        _value(NULL),
        _valueLength(0)
    {
        //empty
    }

    BLERemoteDescriptor::~BLERemoteDescriptor()
    {
        if (_value) 
        {
            free(_value);
            _value = NULL;
        }
    }

    const uint8_t* BLERemoteDescriptor::value() const
    {
        return _value;
    }

    int BLERemoteDescriptor::valueLength() const
    {
        return _valueLength;
    }

    uint8_t BLERemoteDescriptor::operator[] (int offset) const
    {
        if (_value) 
        {
            return _value[offset];
        }

        return 0;
    }

    int BLERemoteDescriptor::writeValue(const uint8_t value[], int length)
    {
        //TO DO
        return 1;
    }

    bool BLERemoteDescriptor::read()
    {
        //TO DO
        return true;
    }

    uint16_t BLERemoteDescriptor::handle() const
    {
        return _handle;
    }
}

