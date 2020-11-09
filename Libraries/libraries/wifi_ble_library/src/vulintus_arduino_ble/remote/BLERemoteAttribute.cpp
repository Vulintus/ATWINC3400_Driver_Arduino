#include "vulintus_arduino_ble/utility/BLEUuid.h"
#include "vulintus_arduino_ble/remote/BLERemoteAttribute.h"

namespace VulintusArduinoBLE
{
    BLERemoteAttribute::BLERemoteAttribute(const uint8_t uuid[], uint8_t uuidLen) :
        _uuid(BLEUuid::uuidToString(uuid, uuidLen)),
        _refCount(0)
    {
        //empty
    }

    BLERemoteAttribute::~BLERemoteAttribute()
    {
        //empty
    }

    const char* BLERemoteAttribute::uuid() const
    {
        return _uuid.c_str();
    }

    int BLERemoteAttribute::retain()
    {
        _refCount++;
        return _refCount;
    }

    int BLERemoteAttribute::release()
    {
        _refCount--;
        return _refCount;
    }
}

