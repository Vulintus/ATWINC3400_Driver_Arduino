#ifndef VULINTUS_ARDUINO_BLE_LOCAL_SERVICE_H
#define VULINTUS_ARDUINO_BLE_LOCAL_SERVICE_H

#include "vulintus_arduino_ble/BLECharacteristic.h"
#include "vulintus_arduino_ble/local/BLELocalAttribute.h"
#include "vulintus_arduino_ble/utility/BLELinkedList.h"

namespace VulintusArduinoBLE
{
    class BLELocalCharacteristic;

    class BLELocalService : public BLELocalAttribute 
    {
        public:
            BLELocalService(const char* uuid);
            virtual ~BLELocalService();

            virtual enum BLEAttributeType type() const;

            void addCharacteristic(BLECharacteristic& characteristic);

        protected:
            friend class ATTClass;
            friend class GATTClass;

            void setHandles(uint16_t start, uint16_t end);
            uint16_t startHandle() const;
            uint16_t endHandle() const;

            unsigned int characteristicCount() const;
            BLELocalCharacteristic* characteristic(unsigned int index) const;

            void addCharacteristic(BLELocalCharacteristic* characteristic);

        private:
            uint16_t _startHandle;
            uint16_t _endHandle;

            BLELinkedList<BLELocalCharacteristic*> _characteristics;
    };
}

#endif /* VULINTUS_ARDUINO_BLE_LOCAL_SERVICE_H */
