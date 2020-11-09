#ifndef VULINTUS_ARDUINO_BLE_DESCRIPTOR_H
#define VULINTUS_ARDUINO_BLE_DESCRIPTOR_H

#include <stdint.h>

namespace VulintusArduinoBLE
{
    class BLELocalDescriptor;
    class BLERemoteDescriptor;

    class BLEDescriptor 
    {
        public:
            BLEDescriptor();
            BLEDescriptor(const BLEDescriptor& other);
            BLEDescriptor(const char* uuid, const uint8_t value[], int valueSize);
            BLEDescriptor(const char* uuid, const char* value);
            virtual ~BLEDescriptor();

            const char* uuid() const;

            int valueSize() const;
            const uint8_t* value() const;
            int valueLength() const;
            uint8_t operator[] (int offset) const;

            int readValue(uint8_t value[], int length);
            int readValue(void* value, int length);
            int readValue(uint8_t& value);
            int readValue(int8_t& value);
            int readValue(uint16_t& value);
            int readValue(int16_t& value);
            int readValue(uint32_t& value);
            int readValue(int32_t& value);

            operator bool() const;

            bool read();

        protected:
            friend class BLELocalCharacteristic;

            BLEDescriptor(BLELocalDescriptor* local);

            BLELocalDescriptor* local();

        protected:
            friend class BLECharacteristic;

            BLEDescriptor(BLERemoteDescriptor* remote);

        private:
            BLELocalDescriptor* _local;
            BLERemoteDescriptor* _remote;
    };

}




#endif /* VULINTUS_ARDUINO_BLE_DESCRIPTOR_H */
