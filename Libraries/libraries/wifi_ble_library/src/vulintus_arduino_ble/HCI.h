#ifndef VULINTUS_ARDUINO_BLE_HCI_H
#define VULINTUS_ARDUINO_BLE_HCI_H

#include <Arduino.h>


namespace VulintusArduinoBLE
{
    class HCIClass 
    {
        public:
            HCIClass();
            virtual ~HCIClass();

            void poll();

            int readBdAddr(uint8_t addr[6]);
            int readRssi(uint16_t handle);

            int leSetRandomAddress(uint8_t addr[6]);



            int leCreateConn(uint16_t interval, uint16_t window, uint8_t initiatorFilter,
                            uint8_t peerBdaddrType, uint8_t peerBdaddr[6], uint8_t ownBdaddrType,
                            uint16_t minInterval, uint16_t maxInterval, uint16_t latency,
                            uint16_t supervisionTimeout, uint16_t minCeLength, uint16_t maxCeLength);
            int leConnUpdate(uint16_t handle, uint16_t minInterval, uint16_t maxInterval, 
                            uint16_t latency, uint16_t supervisionTimeout);
            int leCancelConn();

            int disconnect(uint16_t handle);
        private:
            at_ble_event_parameter_t gu8BleParam;

            void ble_event_manager(at_ble_events_t events, void *event_params);
    };

    extern HCIClass HCI;
}


#endif /* VULINTUS_ARDUINO_BLE_HCI_H */
