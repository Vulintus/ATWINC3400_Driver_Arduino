/*
  This file is part of the ArduinoBLE library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

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

/*
    This version of the file has been modified to be a part of the 
    Vulintus Arduino BLE library.
*/

#ifndef VULINTUS_ARDUINO_BLE_STRING_CHARACTERISTIC_H
#define VULINTUS_ARDUINO_BLE_STRING_CHARACTERISTIC_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLECharacteristic.h"

namespace VulintusArduinoBLE
{
    class BLEStringCharacteristic : public BLECharacteristic
    {
        public:
            BLEStringCharacteristic(const char* uuid, unsigned char properties, int valueSize);

            int writeValue(const String& value);
            String value(void);

        private:
    };
}

#endif /* VULINTUS_ARDUINO_BLE_STRING_CHARACTERISTIC_H */
