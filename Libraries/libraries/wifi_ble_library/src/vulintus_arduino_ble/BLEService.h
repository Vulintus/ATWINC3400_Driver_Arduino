/*
 *  Implementation of the ArduinoBLE API for the ATWINC3400
 *  Author: David Pruitt
 *  Date: 2 November 2020
 */

#ifndef __VULINTUS_ARDUINO_BLESERVICE_H
#define __VULINTUS_ARDUINO_BLESERVICE_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLECharacteristic.h"

namespace VulintusArduinoBLE
{
    class BLELocalService;
    class BLERemoteService;

    class BLEService
    {
        public:
            BLEService();
            BLEService(const char* uuid);
            BLEService(const BLEService& other);
            virtual ~BLEService();

            const char* uuid() const;

            void addCharacteristic(BLECharacteristic& characteristic);

            operator bool() const;

            int characteristicCount() const;
            bool hasCharacteristic(const char* uuid) const;
            bool hasCharacteristic(const char* uuid, int index) const;
            BLECharacteristic characteristic(int index) const;
            BLECharacteristic characteristic(const char * uuid) const;
            BLECharacteristic characteristic(const char * uuid, int index) const;

        protected:
            friend class GATTClass;

            BLEService(BLELocalService* local);

            BLELocalService* local();

            void addCharacteristic(BLELocalCharacteristic* characteristic);

        protected:
            friend class BLEDevice;

            BLEService(BLERemoteService* remote);

        private:
            BLELocalService* _local;
            BLERemoteService* _remote;
    };
}

#endif /* __VULINTUS_ARDUINO_BLESERVICE_H */