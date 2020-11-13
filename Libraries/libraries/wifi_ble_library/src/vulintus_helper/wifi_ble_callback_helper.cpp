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

#include <Arduino.h>

#include "WiFi101.h"
#include "ArduinoBLE.h"

extern WiFiClass WiFi;
extern VulintusArduinoBLE::BLELocalDevice BLE;

void wifi_cb(uint8_t u8MsgType, void *pvMsg)
{
    Serial.println("In wifi ble callback function");
    WiFi.handleEvent(u8MsgType, pvMsg);
}