#ifndef VULINTUS_ARDUINO_BLE_LOCAL_ATTRIBUTE_H
#define VULINTUS_ARDUINO_BLE_LOCAL_ATTRIBUTE_H

#include "utility/BLEUuid.h"

namespace VulintusArduinoBLE
{
    enum BLEAttributeType 
    {
        BLETypeUnknown        = 0x0000,
        BLETypeService        = 0x2800,
        BLETypeCharacteristic = 0x2803,
        BLETypeDescriptor     = 0x2900
    };

    class BLELocalAttribute
    {
        public:
            BLELocalAttribute(const char* uuid);
            virtual ~BLELocalAttribute();

            const char* uuid() const;

            virtual enum BLEAttributeType type() const;

            int retain();
            int release();

        protected:
            friend class ATTClass;
            friend class GATTClass;

            const uint8_t* uuidData() const;
            uint8_t uuidLength() const;

        private:
            BLEUuid _uuid;
            int _refCount;
    };

}

#endif /* VULINTUS_ARDUINO_BLE_LOCAL_ATTRIBUTE_H */
