#ifndef __VULINTUS_ARDUINO_BLE_ATT_H
#define __VULINTUS_ARDUINO_BLE_ATT_H

#define VULINTUS_ARDUINO_BLE_ATT_MAX_PEERS 3

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

namespace VulintusArduinoBLE
{
    struct PeerConnection
    {
        at_ble_addr_t peer_address;
        at_ble_handle_t connection_handle;
    };

    class ATTClass
    {
        public:

            ATTClass ();
            ~ATTClass ();

            void SendIndication (at_ble_handle_t value_handle);
            void SendNotification (at_ble_handle_t value_handle);

        private:

            PeerConnection peers [VULINTUS_ARDUINO_BLE_ATT_MAX_PEERS];
            int current_peer_count;

    };

    extern ATTClass ATT;
}

#endif /* __VULINTUS_ARDUINO_BLE_ATT_H */