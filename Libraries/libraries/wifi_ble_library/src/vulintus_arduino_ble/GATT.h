#ifndef VULINTUS_ARDUINO_BLE_GATT_H
#define VULINTUS_ARDUINO_BLE_GATT_H

#include "vulintus_arduino_ble/utility/BLELinkedList.h"

#include "vulintus_arduino_ble/local/BLELocalAttribute.h"
#include "vulintus_arduino_ble/local/BLELocalCharacteristic.h"
#include "vulintus_arduino_ble/local/BLELocalService.h"

#include "vulintus_arduino_ble/BLEService.h"

namespace VulintusArduinoBLE
{
    class GATTClass 
    {
        public:
            GATTClass();
            virtual ~GATTClass();

            void begin();
            void end();

            void setDeviceName(const char* deviceName);
            void setAppearance(uint16_t appearance);

            void addService(BLEService& service);

        protected:
            friend class ATTClass;

            unsigned int attributeCount() const;
            BLELocalAttribute* attribute(unsigned int index) const;

        protected:
            friend class BLELocalCharacteristic;

            uint16_t serviceUuidForCharacteristic(BLELocalCharacteristic* characteristic) const;

        private:
            void addService(BLELocalService* service);

            void clearAttributes();

        private:
            BLELinkedList<BLELocalAttribute*> _attributes;

            BLELocalService              _genericAccessService;
            BLELocalCharacteristic       _deviceNameCharacteristic;
            BLELocalCharacteristic       _appearanceCharacteristic;
            BLELocalService              _genericAttributeService;
            BLELocalCharacteristic       _servicesChangedCharacteristic;
    };

    extern GATTClass GATT;
}


#endif /* VULINTUS_ARDUINO_BLE_GATT_H */
