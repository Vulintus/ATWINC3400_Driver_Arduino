#ifndef VULINTUS_ARDUINO_BLE_LOCAL_DESCRIPTOR_H
#define VULINTUS_ARDUINO_BLE_LOCAL_DESCRIPTOR_H

#include <stdint.h>

#include "vulintus_arduino_ble/local/BLELocalAttribute.h"

namespace VulintusArduinoBLE
{
    class BLELocalDescriptor : public BLELocalAttribute 
    {
        public:
            BLELocalDescriptor(const char* uuid, const uint8_t value[], int valueSize);
            BLELocalDescriptor(const char* uuid, const char* value);
            virtual ~BLELocalDescriptor();

            virtual enum BLEAttributeType type() const;

            int valueSize() const;
            const uint8_t* value() const;
            uint8_t operator[] (int offset) const;

        protected:
            friend class GATTClass;

            void setHandle(uint16_t handle);
            uint16_t handle() const;

        private:
            const uint8_t* _value;
            int            _valueSize;

            uint16_t       _handle;
    };
}


#endif /* VULINTUS_ARDUINO_BLE_LOCAL_DESCRIPTOR_H */
