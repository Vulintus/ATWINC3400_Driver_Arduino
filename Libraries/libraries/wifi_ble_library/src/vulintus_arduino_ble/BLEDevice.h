/*
 *  Implementation of the ArduinoBLE API for the ATWINC3400
 *  Author: David Pruitt
 *  Date: 2 November 2020
 */

#ifndef __VULINTUS_ARDUINO_BLEDEVICE_H
#define __VULINTUS_ARDUINO_BLEDEVICE_H

#include <Arduino.h>

namespace VulintusArduinoBLE
{
    enum BLEDeviceEvent 
    {
        BLEConnected = 0,
        BLEDisconnected = 1,
        BLEDiscovered = 2,
        BLEDeviceLastEvent
    };

    class BLEDevice;

    typedef void (*BLEDeviceEventHandler)(BLEDevice device);

    class BLEDevice
    {
        public:

            BLEDevice()
            {

            }
    };
}


#endif /* __VULINTUS_ARDUINO_BLEDEVICE_H */