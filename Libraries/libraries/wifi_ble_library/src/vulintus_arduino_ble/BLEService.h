#ifndef __VULINTUS_ARDUINO_BLE_SERVICE_H
#define __VULINTUS_ARDUINO_BLE_SERVICE_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLEUuid.h"
#include "vulintus_arduino_ble/BLECharacteristic.h"
#include "vulintus_arduino_ble/BLELinkedList.h"

#define VULINTUS_BLE_MAX_CHARACTERISTICS_PER_SERVICE    3

namespace VulintusArduinoBLE
{
    class BLEService
    {
        public:

            BLEService();
            BLEService(const char * uuid);
            ~BLEService();

            void AddCharacteristic (BLECharacteristic &characteristic);

            at_ble_handle_t GetServiceHandle ();
            String GetServiceUUID ();

        private:
            friend class BLELocalDevice;

            at_ble_handle_t service_handle;
            BLEUuid service_uuid;

            BLELinkedList<BLECharacteristic*> service_characteristics;
    };
}

#endif /* __VULINTUS_ARDUINO_BLE_SERVICE_H */