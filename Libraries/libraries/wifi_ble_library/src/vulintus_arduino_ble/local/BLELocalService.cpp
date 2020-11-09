#include "vulintus_arduino_ble/local/BLELocalCharacteristic.h"
#include "vulintus_arduino_ble/local/BLELocalService.h"

namespace VulintusArduinoBLE
{
    BLELocalService::BLELocalService(const char* uuid) :
        BLELocalAttribute(uuid),
        _startHandle(0x0000),
        _endHandle(0x0000)
    {
        //empty
    }

    BLELocalService::~BLELocalService()
    {
        for (unsigned int i = 0; i < characteristicCount(); i++) 
        {
            BLELocalCharacteristic* c = characteristic(i);

            if (c->release() <= 0) 
            {
                delete c;
            }
        }

        _characteristics.clear();
    }

    enum BLEAttributeType BLELocalService::type() const
    {
        return BLETypeService;
    }

    void BLELocalService::addCharacteristic(BLECharacteristic& characteristic)
    {
        BLELocalCharacteristic* localCharacteristic = characteristic.local();

        if (localCharacteristic) 
        {
            addCharacteristic(localCharacteristic);
        }
    }

    void BLELocalService::setHandles(uint16_t start, uint16_t end)
    {
        _startHandle = start;
        _endHandle = end;
    }

    uint16_t BLELocalService::startHandle() const
    {
        return _startHandle;
    }

    uint16_t BLELocalService::endHandle() const
    {
        return _endHandle;
    }

    unsigned int BLELocalService::characteristicCount() const
    {
        return _characteristics.size();
    }

    BLELocalCharacteristic* BLELocalService::characteristic(unsigned int index) const
    {
        return _characteristics.get(index);
    }

    void BLELocalService::addCharacteristic(BLELocalCharacteristic* characteristic)
    {
        characteristic->retain();
        _characteristics.add(characteristic);
    }
}

