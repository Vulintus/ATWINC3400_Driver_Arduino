#include "vulintus_arduino_ble/ATT.h"

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

namespace VulintusArduinoBLE
{
    ATTClass::ATTClass ()
    {
        current_peer_count = 0;
    }

    ATTClass::~ATTClass ()
    {
        //empty
    }

    void ATTClass::SendIndication (at_ble_handle_t value_handle)
    {
        for (int i = 0; i < current_peer_count; i++)
        {
            at_ble_indication_send(peers[i].connection_handle, value_handle);
        }
    }

    void ATTClass::SendNotification (at_ble_handle_t value_handle)
    {
        for (int i = 0; i < current_peer_count; i++)
        {
            at_ble_notification_send(peers[i].connection_handle, value_handle);
        }
    }

    ATTClass ATT;
}