#ifndef VULINTUS_ARDUINO_BLE_REMOTE_DESCRIPTOR_H
#define VULINTUS_ARDUINO_BLE_REMOTE_DESCRIPTOR_H

#include "vulintus_arduino_ble/remote/BLERemoteAttribute.h"

namespace VulintusArduinoBLE
{
    class BLERemoteDescriptor : public BLERemoteAttribute 
    {
        public:
            BLERemoteDescriptor(const uint8_t uuid[], uint8_t uuidLen, uint16_t connectionHandle, uint16_t handle);
            virtual ~BLERemoteDescriptor();

            const uint8_t* value() const;
            int valueLength() const;
            uint8_t operator[] (int offset) const;

            int writeValue(const uint8_t value[], int length);

            bool read();

        protected:
            friend class ATTClass;
            uint16_t handle() const;

        private:
            uint16_t _connectionHandle;
            uint16_t _handle;

            uint8_t* _value;
            int _valueLength;
    };
}


#endif /* VULINTUS_ARDUINO_BLE_REMOTE_DESCRIPTOR_H */
