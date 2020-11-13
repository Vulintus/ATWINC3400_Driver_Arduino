#ifndef __VULINTUS_ARDUINO_BLE_REMOTE_DEVICE_H
#define __VULINTUS_ARDUINO_BLE_REMOTE_DEVICE_H

#include <Arduino.h>

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
    #include "ble/atmel_ble_api/include/m2m_ble.h"
}

#include "vulintus_arduino_ble/BLEPeerConnection.h"
#include "vulintus_arduino_ble/ATT.h"

namespace VulintusArduinoBLE
{
    class BLERemoteDevice
    {
        public:

            BLERemoteDevice();
            BLERemoteDevice(at_ble_addr_t address, at_ble_handle_t handle);
            BLERemoteDevice(BLEPeerConnection connection);
            ~BLERemoteDevice();

            virtual operator bool() const;

            String GetAddress (bool include_addr_type = false);
            bool IsConnected ();

        private:

            BLEPeerConnection peer_connection;

    };
}

#endif /* __VULINTUS_ARDUINO_BLE_REMOTE_DEVICE_H */