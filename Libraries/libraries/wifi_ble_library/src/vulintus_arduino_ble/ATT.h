#ifndef __VULINTUS_ARDUINO_BLE_ATT_H
#define __VULINTUS_ARDUINO_BLE_ATT_H

#include <Arduino.h>

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
    #include "ble/atmel_ble_api/include/m2m_ble.h"
}

#include "vulintus_arduino_ble/BLELinkedList.h"
#include "vulintus_arduino_ble/BLEPeerConnection.h"

namespace VulintusArduinoBLE
{
    class ATTClass
    {
        public:

            ATTClass ();
            ~ATTClass ();

            void SendIndication (at_ble_handle_t value_handle);
            void SendNotification (at_ble_handle_t value_handle);

            BLEPeerConnection GetFirstPeerConnectionOrDefault ();
            bool DoesConnectionExist (BLEPeerConnection connection);
            void ProcessEvents ();
            
        private:

            at_ble_event_parameter_t gu8BleParam;
            void ble_event_manager(at_ble_events_t events, void *event_params);

            BLELinkedList<BLEPeerConnection> peers;

    };

    extern ATTClass ATT;
}

#endif /* __VULINTUS_ARDUINO_BLE_ATT_H */