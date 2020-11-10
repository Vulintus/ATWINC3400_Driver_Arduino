#ifndef __VULINTUS_ARDUINO_BLE_LOCALDEVICE_H
#define __VULINTUS_ARDUINO_BLE_LOCALDEVICE_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLEService.h"
#include "vulintus_arduino_ble/BLELinkedList.h"

namespace VulintusArduinoBLE
{
    class BLELocalDevice
    {
        public:

            BLELocalDevice();
            ~BLELocalDevice();

            int Begin ();
            int SetDeviceName(const char* deviceName);
            int AddService (BLEService &service);
            void SetAdvertisedServiceUUID (BLEUuid &uuid);
            void SetAdvertisedService (BLEService &service);
            int Advertise ();

            String GetAddress (bool include_addr_type = false);

        private:

            bool currently_advertising;
            uint16_t advertising_interval;
            BLEUuid advertised_service_uuid;
            String device_name;
            BLELinkedList<BLEService*> services_list;
    };

    extern BLELocalDevice BLE;
}

#endif /* __VULINTUS_ARDUINO_BLE_LOCALDEVICE_H */