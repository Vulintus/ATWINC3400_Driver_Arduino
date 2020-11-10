#include "vulintus_arduino_ble/BLEService.h"

namespace VulintusArduinoBLE
{
    /// <summary>
    /// Constructor
    /// </summary>
    BLEService::BLEService()
    {
        service_characteristics = BLELinkedList<BLECharacteristic*>();
    }

    BLEService::BLEService(const char *uuid) :
        service_uuid(uuid)
    {
        service_characteristics = BLELinkedList<BLECharacteristic*>();
    }

    /// <summary>
    /// Destructor
    /// </summary>
    BLEService::~BLEService()
    {
        //empty
    }

    void BLEService::AddCharacteristic (BLECharacteristic &characteristic)
    {
        if (service_characteristics.size() < VULINTUS_BLE_MAX_CHARACTERISTICS_PER_SERVICE)
        {
            service_characteristics.add(&characteristic);
        }
    }

    at_ble_handle_t BLEService::GetServiceHandle ()
    {
        return service_handle;
    }

    String BLEService::GetServiceUUID ()
    {
        String result = service_uuid.str();
        return result;
    }
}