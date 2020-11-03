/*
 *  Implementation of the ArduinoBLE API for the ATWINC3400
 *  Author: David Pruitt
 *  Date: 2 November 2020
 */

#ifndef __VULINTUS_ARDUINO_BLELOCALDEVICE_H
#define __VULINTUS_ARDUINO_BLELOCALDEVICE_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLEDevice.h"
#include "vulintus_arduino_ble/BLEService.h"

namespace VulintusArduinoBLE
{
    class BLELocalDevice
    {
        private:

        public:

            BLELocalDevice();
            virtual ~BLELocalDevice();

            int begin();
            void end();

            void poll();
            void poll(unsigned long timeout);

            bool connected() const;
            bool disconnect();

            String address() const;

            int rssi();

            void setAdvertisedServiceUuid(const char* advertisedServiceUuid);
            void setAdvertisedService(const BLEService& service);
            void setManufacturerData(const uint8_t manufacturerData[], int manufacturerDataLength);
            void setManufacturerData(const uint16_t companyId, const uint8_t manufacturerData[], int manufacturerDataLength);
            void setLocalName(const char *localName);

            void setDeviceName(const char* deviceName);
            void setAppearance(uint16_t appearance);

            void addService(BLEService& service);

            int advertise();
            void stopAdvertise();

            int scan(bool withDuplicates = false);
            int scanForName(String name, bool withDuplicates = false);
            int scanForUuid(String uuid, bool withDuplicates = false);
            int scanForAddress(String address, bool withDuplicates = false);
            void stopScan();

            BLEDevice central();
            BLEDevice available();

            void setEventHandler(BLEDeviceEvent event, BLEDeviceEventHandler eventHandler);

            void setAdvertisingInterval(uint16_t advertisingInterval);
            void setConnectionInterval(uint16_t minimumConnectionInterval, uint16_t maximumConnectionInterval);
            void setConnectable(bool connectable); 

            void setTimeout(unsigned long timeout);

            void debug(Stream& stream);
            void noDebug();
    };

    extern BLELocalDevice BLE;
}



#endif /* __VULINTUS_ARDUINO_BLELOCALDEVICE_H */