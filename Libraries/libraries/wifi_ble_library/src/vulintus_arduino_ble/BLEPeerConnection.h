#ifndef __VULINTUS_ARDUINO_BLE_PEER_CONNECTION_H
#define __VULINTUS_ARDUINO_BLE_PEER_CONNECTION_H

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

namespace VulintusArduinoBLE
{
    struct BLEPeerConnection
    {
        at_ble_addr_t peer_address;
        at_ble_handle_t connection_handle;
    };
}

#endif /* __VULINTUS_ARDUINO_BLE_PEER_CONNECTION_H */