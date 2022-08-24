/*
  This file is part of the Vulintus Arduino BLE library.
  Copyright (c) 2020 Vulintus Inc. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

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