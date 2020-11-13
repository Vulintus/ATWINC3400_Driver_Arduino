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

#include "vulintus_arduino_ble/BLEStringCharacteristic.h"

namespace VulintusArduinoBLE
{
    BLEStringCharacteristic::BLEStringCharacteristic(const char* uuid, unsigned char properties, int valueSize) :
        BLECharacteristic(uuid, properties, valueSize)
    {
        //empty
    }

    int BLEStringCharacteristic::writeValue(const String& value)
    {
        return BLECharacteristic::writeValue(value.c_str());
    }

    String BLEStringCharacteristic::value(void)
    {
        String str;
        int length = characteristic_value_size;
        const uint8_t* val = characteristic_value;

        str.reserve(length);

        for (int i = 0; i < length; i++) 
        {
            str += (char)val[i];
        }

        return str;
    }
}

