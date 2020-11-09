#include "vulintus_arduino_ble/local/BLELocalService.h"
#include "vulintus_arduino_ble/remote/BLERemoteService.h"
#include "vulintus_arduino_ble/BLEService.h"

namespace VulintusArduinoBLE
{
    BLEService::BLEService() :
        BLEService((BLELocalService*)NULL)
    {
        //empty
    }

    BLEService::BLEService(BLELocalService* local) :
        _local(local),
        _remote(NULL)
    {
        if (_local) 
        {
            _local->retain();
        }
    }

    BLEService::BLEService(BLERemoteService* remote) :
        _local(NULL),
        _remote(remote)
    {
        if (_remote) 
        {
            _remote->retain();
        }
    }

    BLEService::BLEService(const char* uuid) :
        BLEService(new BLELocalService(uuid))
    {
        //empty
    }

    BLEService::BLEService(const BLEService& other)
    {
        _local = other._local;
        if (_local) 
        {
            _local->retain();
        }

        _remote = other._remote;
        if (_remote) 
        {
            _remote->retain();
        }
    }

    BLEService::~BLEService()
    {
        if (_local && _local->release() <= 0) 
        {
            delete _local;
        }

        if (_remote && _remote->release() <= 0) 
        {
            delete _remote;
        }
    }

    const char* BLEService::uuid() const
    {
        if (_local) 
        {
            return _local->uuid();
        }

        if (_remote) 
        {
            return _remote->uuid();
        }

        return "";
    }

    void BLEService::addCharacteristic(BLECharacteristic& characteristic)
    {
        if (_local) 
        {
            _local->addCharacteristic(characteristic);
        }
    }

    BLEService::operator bool() const
    {
        return (_local != NULL) || (_remote != NULL);
    }

    int BLEService::characteristicCount() const
    {
        if (_remote) 
        {
            return _remote->characteristicCount();
        }

        return 0;
    }

    bool BLEService::hasCharacteristic(const char* uuid) const
    {
        return hasCharacteristic(uuid, 0);
    }

    bool BLEService::hasCharacteristic(const char* uuid, int index) const
    {
        if (_remote) 
        {
            int count = 0;
            int numCharacteristics = _remote->characteristicCount();

            for (int i = 0; i < numCharacteristics; i++) 
            {
                BLERemoteCharacteristic* c = _remote->characteristic(i);

                if (strcasecmp(uuid, c->uuid()) == 0) 
                {
                    if (count == index) 
                    {
                        return true;
                    }

                    count++;
                }
            }
        }

        return false;
    }

    BLECharacteristic BLEService::characteristic(int index) const
    {
        if (_remote) 
        {
            return BLECharacteristic(_remote->characteristic(index));
        }

        return BLECharacteristic();
    }

    BLECharacteristic BLEService::characteristic(const char * uuid) const
    {
        return characteristic(uuid, 0);
    }

    BLECharacteristic BLEService::characteristic(const char * uuid, int index) const
    {
        if (_remote) 
        {
            int count = 0;
            int numCharacteristics = _remote->characteristicCount();

            for (int i = 0; i < numCharacteristics; i++) 
            {
                BLERemoteCharacteristic* c = _remote->characteristic(i);

                if (strcasecmp(uuid, c->uuid()) == 0) 
                {
                    if (count == index) 
                    {
                        return BLECharacteristic(c);
                    }

                    count++;
                }
            }
        }

        return BLECharacteristic();
    }

    BLELocalService* BLEService::local()
    {
        return _local;
    }
}