#ifndef __VULINTUS_ARDUINO_BLE_LOCALDEVICE_H
#define __VULINTUS_ARDUINO_BLE_LOCALDEVICE_H

#include <Arduino.h>

#include "vulintus_arduino_ble/BLEService.h"
#include "vulintus_arduino_ble/BLELinkedList.h"
#include "vulintus_arduino_ble/BLERemoteDevice.h"
#include "vulintus_arduino_ble/ATT.h"
#include "vulintus_arduino_ble/BLEPeerConnection.h"

namespace VulintusArduinoBLE
{
    /// <summary>
    /// An enumeration defining the codes for different advertising data types.
    /// </summary>
    enum BLEAdvertisingDataType
    {
        //The master list of data types can be found at the following link:
        //https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile/

        BLE_ADV_DATATYPE_FLAGS = 0x01,
        BLE_ADV_DATATYPE_INCOMPLETE_LIST_UUID_16BIT = 0x02,
        BLE_ADV_DATATYPE_COMPLETE_LIST_UUID_16BIT = 0x03,
        BLE_ADV_DATATYPE_INCOMPLETE_LIST_UUID_32BIT = 0x04,
        BLE_ADV_DATATYPE_COMPLETE_LIST_UUID_32BIT = 0x05,
        BLE_ADV_DATATYPE_INCOMPLETE_LIST_UUID_128BIT = 0x06,
        BLE_ADV_DATATYPE_COMPLETE_LIST_UUID_128BIT = 0x07,
        BLE_ADV_DATATYPE_SHORTENED_LOCAL_NAME = 0x08,
        BLE_ADV_DATATYPE_COMPLETE_LOCAL_NAME = 0x09,
        BLE_ADV_DATATYPE_TX_POWER_LEVEL = 0x0A,
        BLE_ADV_DATATYPE_CLASS_OF_DEVICE = 0x0D,
        BLE_ADV_DATATYPE_SIMPLE_PAIRING_HASH_C = 0x0E,
        BLE_ADV_DATATYPE_SIMPLE_PAIRING_HASH_C192 = 0x0E,
        BLE_ADV_DATATYPE_SIMPLE_PAIRING_RANDOMIZER_R = 0x0F,
        BLE_ADV_DATATYPE_SIMPLE_PAIRING_RANDOMIZER_R192 = 0x0F,
        BLE_ADV_DATATYPE_DEVICE_ID = 0x10,
        BLE_ADV_DATATYPE_SECURITY_MANAGER_TK_VALUE = 0x10,
        BLE_ADV_DATATYPE_SECURITY_MANAGER_OUT_OF_BAND_FLAGS = 0x11,
        BLE_ADV_DATATYPE_SLAVE_CONNECTION_INTERVAL_RANGE = 0x12,
        BLE_ADV_DATATYPE_LIST_16BIT_UUID_SOLICITATION = 0x14,
        BLE_ADV_DATATYPE_LIST_128BIT_UUID_SOLICITATION = 0x15,
        BLE_ADV_DATATYPE_SERVICE_DATA = 0x16,
        BLE_ADV_DATATYPE_SERVICE_DATA_16BIT_UUID = 0x16,
        BLE_ADV_DATATYPE_PUBLIC_TARGET_ADDRESS = 0x17,
        BLE_ADV_DATATYPE_RANDOM_TARGET_ADDRESS = 0x18,
        BLE_ADV_DATATYPE_APPEARANCE = 0x19,
        BLE_ADV_DATATYPE_ADVERTISING_INTERVAL = 0x1A,
        BLE_ADV_DATATYPE_LE_BLUETOOTH_DEVICE_ADDRESS = 0x1B,
        BLE_ADV_DATATYPE_LE_ROLE = 0x1C,
        BLE_ADV_DATATYPE_SIMPLE_PAIRING_HASH_C256 = 0x1D,
        BLE_ADV_DATATYPE_SIMPLE_PAIRING_RANDOMIZER_R256 = 0x1E,
        BLE_ADV_DATATYPE_LIST_32BIT_UUID_SOLICITATION = 0x1F,
        BLE_ADV_DATATYPE_SERVICE_DATA_32BIT_UUID = 0x20,
        BLE_ADV_DATATYPE_SERVICE_DATA_128BIT_UUID = 0x21,
        BLE_ADV_DATATYPE_LE_SECURE_CONNECTIONS_CONFIRMATION_VAL = 0x22,
        BLE_ADV_DATATYPE_LE_SECURE_CONNECTIONS_RANDOM_VAL = 0x23,
        BLE_ADV_DATATYPE_URI = 0x24,
        BLE_ADV_DATATYPE_INDOOR_POSITIONING = 0x25,
        BLE_ADV_DATATYPE_TRANSPORT_DISCOVERY_DATA = 0x26,
        BLE_ADV_DATATYPE_LE_SUPPORTED_FEATURES = 0x27,
        BLE_ADV_DATATYPE_CHANNEL_MAP_UPDATE_INDICATION = 0x28,
        BLE_ADV_DATATYPE_PB_ADV = 0x29,
        BLE_ADV_DATATYPE_MESH_MESSAGE = 0x2A,
        BLE_ADV_DATATYPE_MESH_BEACON = 0x2B,
        BLE_ADV_DATATYPE_BIG_INFO = 0x2C,
        BLE_ADV_DATATYPE_BROADCAST_CODE = 0x2D,
        BLE_ADV_DATATYPE_3D_INFORMATION_DATA = 0x3D,
        BLE_ADV_DATA_MANUFACTURER_SPECIFIC_DATA = 0xFF
    };

    /// <summary>
    /// An enumeration of advertising flags used when constructing the advertising data packet when we are about
    /// to advertise this BLE device.
    /// </summary>
    enum BLEAdvertisingFlags
    {
        //Terminology note: "BR" means "basic rate", "EDR" means "enhanced data rate"
        //As far as I know, "BR/EDR" support basically means you support "classic" Bluetooth connections

        BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE = 0x01, /**< LE Limited Discoverable Mode. */
        BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE = 0x02, /**< LE General Discoverable Mode. */
        BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED = 0x04, /**< BR/EDR not supported. */
        BLE_GAP_ADV_FLAG_LE_BR_EDR_CONTROLLER = 0x08, /**< Simultaneous LE and BR/EDR, Controller. */
        BLE_GAP_ADV_FLAG_LE_BR_EDR_HOST = 0x10        /**< Simultaneous LE and BR/EDR, Host. */
    };

    /// <summary>
    /// A class that represents this BLE device.
    /// </summary>
    class BLELocalDevice
    {
        public:

            BLELocalDevice();
            ~BLELocalDevice();

            int Begin ();
            int SetDeviceName(const char* deviceName);
            int AddService (BLEService &service);
            void SetAdvertisedServiceUUID (BLEUuid &uuid);
            void SetAdvertisedService (BLEService &service);
            int Advertise ();

            String GetAddress (bool include_addr_type = false);
            void ProcessEvents ();
            BLERemoteDevice GetCentralDevice ();

        private:

            bool currently_advertising;
            uint16_t advertising_interval;
            BLEUuid advertised_service_uuid;
            String device_name;
            BLELinkedList<BLEService*> services_list;
    };

    extern BLELocalDevice BLE;
}

#endif /* __VULINTUS_ARDUINO_BLE_LOCALDEVICE_H */