#ifndef VULINTUS_ARDUINO_BLE_GAP_H
#define VULINTUS_ARDUINO_BLE_GAP_H

#include <Arduino.h>

#include "vulintus_arduino_ble/utility/BLELinkedList.h"
#include "vulintus_arduino_ble/BLEDevice.h"

namespace VulintusArduinoBLE
{
    class GAPClass 
    {
        public:
            GAPClass();
            virtual ~GAPClass();

            void setAdvertisedServiceUuid(const char* advertisedServiceUuid);
            void setManufacturerData(const uint8_t manufacturerData[], int manufacturerDataLength);
            void setManufacturerData(const uint16_t companyId, const uint8_t manufacturerData[], int manufacturerDataLength);
            void setLocalName(const char *localName);

            bool advertising();
            int advertise();
            void stopAdvertise();

            int scan(bool withDuplicates);
            int scanForName(String name, bool withDuplicates);
            int scanForUuid(String uuid, bool withDuplicates);
            int scanForAddress(String address, bool withDuplicates);
            void stopScan();
            BLEDevice available();

            void setAdvertisingInterval(uint16_t advertisingInterval);
            void setConnectable(bool connectable);

            void setEventHandler(BLEDeviceEvent event, BLEDeviceEventHandler eventHandler);

        protected:
            friend class BLELocalCharacteristic;

            void setAdvertisedServiceData(uint16_t uuid, const uint8_t data[], int length);

        protected:
            friend class HCIClass;

            void handleLeAdvertisingReport(uint8_t type, uint8_t addressType, uint8_t address[6], 
                                           uint8_t eirLength, uint8_t eirData[], int8_t rssi);

        private:
            bool matchesScanFilter(const BLEDevice& device);

        private:
            bool _advertising;
            bool _scanning;

            const char* _advertisedServiceUuid;
            const uint8_t* _manufacturerData;
            int _manufacturerDataLength;
            const char* _localName;
            uint16_t _advertisingInterval;
            bool _connectable;

            uint16_t _serviceDataUuid;
            const uint8_t* _serviceData;
            int _serviceDataLength;

            BLEDeviceEventHandler _discoverEventHandler;
            BLELinkedList<BLEDevice*> _discoveredDevices;

            String _scanNameFilter;
            String _scanUuidFilter;
            String _scanAddressFilter;           
    };

    extern GAPClass GAP;
}


#endif /* VULINTUS_ARDUINO_BLE_GAP_H */
