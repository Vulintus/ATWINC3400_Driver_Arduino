#include "vulintus_arduino_ble/local/BLELocalAttribute.h"

namespace VulintusArduinoBLE
{
    BLELocalAttribute::BLELocalAttribute(const char* uuid) 
        : _uuid(uuid), _refCount(0)
    {
        //empty
    }

    BLELocalAttribute::~BLELocalAttribute()
    {
        //empty
    }

    const char* BLELocalAttribute::uuid() const
    {
        return _uuid.str();
    }

    const uint8_t* BLELocalAttribute::uuidData() const
    {
        return _uuid.data();
    }

    uint8_t BLELocalAttribute::uuidLength() const
    {
        return _uuid.length();
    }

    enum BLEAttributeType BLELocalAttribute::type() const
    {
        return BLETypeUnknown;
    }

    int BLELocalAttribute::retain()
    {
        _refCount++;
        return _refCount;
    }

    int BLELocalAttribute::release()
    {
        _refCount--;
        return _refCount;
    }
}