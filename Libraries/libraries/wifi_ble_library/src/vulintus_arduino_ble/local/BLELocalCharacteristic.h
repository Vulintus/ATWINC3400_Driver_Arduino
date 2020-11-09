#ifndef VULINTUS_ARDUINO_BLE_LOCAL_CHARACTERISTIC_H
#define VULINTUS_ARDUINO_BLE_LOCAL_CHARACTERISTIC_H

#include <stdint.h>

#include "vulintus_arduino_ble/BLECharacteristic.h"
#include "vulintus_arduino_ble/BLEDescriptor.h"
#include "vulintus_arduino_ble/local/BLELocalAttribute.h"
#include "vulintus_arduino_ble/utility/BLELinkedList.h"

namespace VulintusArduinoBLE
{
    class BLELocalDescriptor;

    class BLELocalCharacteristic : public BLELocalAttribute 
    {
        public:
            BLELocalCharacteristic(const char* uuid, uint8_t properties, int valueSize, bool fixedLength = false);
            BLELocalCharacteristic(const char* uuid, uint8_t properties, const char* value);
            virtual ~BLELocalCharacteristic();

            virtual enum BLEAttributeType type() const;

            uint8_t properties() const;

            int valueSize() const;
            const uint8_t* value() const;
            int valueLength() const;
            uint8_t operator[] (int offset) const;

            int writeValue(const uint8_t value[], int length);
            int writeValue(const char* value);

            int broadcast();

            bool written();
            bool subscribed();

            void addDescriptor(BLEDescriptor& descriptor);

            void setEventHandler(BLECharacteristicEvent event, BLECharacteristicEventHandler eventHandler);

        protected:
            friend class ATTClass;
            friend class GATTClass;

            void setHandle(uint16_t handle);
            uint16_t handle() const;
            uint16_t valueHandle() const;

            unsigned int descriptorCount() const;
            BLELocalDescriptor* descriptor(unsigned int index) const;

            void readValue(BLEDevice device, uint16_t offset, uint8_t value[], int length);
            void writeValue(BLEDevice device, const uint8_t value[], int length);
            void writeCccdValue(BLEDevice device, uint16_t value);

        private:
            uint8_t  _properties;
            int      _valueSize;
            uint8_t* _value;
            uint16_t  _valueLength;
            bool _fixedLength;

            uint16_t _handle;

            bool _broadcast;
            bool _written;

            uint16_t _cccdValue;
            BLELinkedList<BLELocalDescriptor*> _descriptors;

            BLECharacteristicEventHandler _eventHandlers[BLECharacteristicEventLast];
};


}




#endif /* VULINTUS_ARDUINO_BLE_LOCAL_CHARACTERISTIC_H */
