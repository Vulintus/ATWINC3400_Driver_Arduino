#include "vulintus_arduino_ble/BLELocalDevice.h"

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
    #include "ble/atmel_ble_api/include/m2m_ble.h"
    #include "driver/include/m2m_periph.h"    
}

extern void wifi_cb(uint8_t u8MsgType, void *pvMsg);

namespace VulintusArduinoBLE
{
    /// <summary>
    /// Constructor
    /// </summary>
    BLELocalDevice::BLELocalDevice()
    {
        currently_advertising = false;
        advertising_interval = 160;
        device_name = "";
        services_list = BLELinkedList<BLEService*>();
    }

    BLELocalDevice::~BLELocalDevice()
    {
        //empty
    }

    int BLELocalDevice::Begin()
    {
        //Set the callback method for the BLE events
        tstrWifiInitParam param;
        m2m_memset((uint8*)&param, 0, sizeof(param));
        param.pfAppWifiCb = wifi_cb;
        sint8 ble_wifi_init_result = m2m_ble_wifi_init(&param);

        //Initialize the BLE stack
        int ble_init_result = m2m_ble_init();

        //Set a default device name
        if (ble_init_result == M2M_SUCCESS)
        {
            String default_device_name = "ATWINC3400BLE";
            at_ble_device_name_set((uint8_t *)default_device_name.c_str(), default_device_name.length());
        }
        
        //Return the result of the initialization process
        return ble_init_result;
    }

    int BLELocalDevice::SetDeviceName(const char* deviceName)
    {
        device_name = deviceName;
        at_ble_status_t status = at_ble_device_name_set((uint8_t *)deviceName, m2m_strlen((const uint8 *)deviceName));
        return status;
    }    

    int BLELocalDevice::AddService (BLEService &service)
    {
        //Add the service to our internal list of services on this device.
        services_list.add(&service);
        Serial.println("ADD SERVICE 1: Added service to internal list");

        //We need to take the list of characteristics from the BLEService object and put it into the form
        //of an at_ble_characteristic_t* to satisfy the conditions of the at_ble_primary_service_define
        //function.
        at_ble_characteristic_t *service_characteristics_list = 
            (at_ble_characteristic_t *) malloc(sizeof(at_ble_characteristic_t) * service.service_characteristics.size());
        for (int i = 0; i < service.service_characteristics.size(); i++)
        {
            BLECharacteristic *temp_characteristic = service.service_characteristics.get(i);
            service_characteristics_list[i] = temp_characteristic->internal_characteristic;
        }
        Serial.println("ADD SERVICE 2: Malloc of list complete");
        for (int i = 0; i < service.service_characteristics.size(); i++)
        {
            Serial.print("Characteristic ");
            Serial.print(i);
            Serial.print(": ");
            Serial.print("uuid = ");
            Serial.print(BLEUuid::uuidToString(service_characteristics_list[i].uuid.uuid, 16));
            Serial.println();
        }

        //Define the service in the BLE stack
        at_ble_status_t result = at_ble_primary_service_define(
            service.service_uuid.get(),
            &service.service_handle,
            NULL,
            0,
            service_characteristics_list,
            service.service_characteristics.size()
        );
        Serial.println("ADD SERVICE 3: Primary service define complete");

        //Now we need to fetch the handles that the stack created and put them back into the BLECharacteristic objects
        for (int i = 0; i < service.service_characteristics.size(); i++)
        {
            BLECharacteristic *temp_characteristic = service.service_characteristics.get(i);
            temp_characteristic->internal_characteristic.char_val_handle = 
                service_characteristics_list[i].char_val_handle;
            Serial.print("ADD SERVICE CHAR HANDLE: ");
            Serial.println(service_characteristics_list[i].char_val_handle);
        }
        Serial.println("ADD SERVICE 4: Transfer of value handles back to original structures complete");

        //Now free the memory we allocated
        free(service_characteristics_list);
        Serial.println("ADD SERVICE 5: Free memory complete");

        //Return the result from the BLE stack
        return result;
    }    

    void BLELocalDevice::SetAdvertisedServiceUUID (BLEUuid &uuid)
    {
        advertised_service_uuid = uuid;
    }

    void BLELocalDevice::SetAdvertisedService (BLEService &service)
    {
        advertised_service_uuid = service.service_uuid;
    }

    int BLELocalDevice::Advertise ()
    {
        //The following link is the most useful link that I have found for describing the format of advertising data:
        //https://www.silabs.com/community/wireless/bluetooth/knowledge-base.entry.html/2017/02/10/bluetooth_advertisin-hGsf

        //The following link defines the possible data types:
        //https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile/

        //The following link defines the possible advertising flags (useful if the chosen data type is 0x01):
        //https://devzone.nordicsemi.com/f/nordic-q-a/29083/ble-advertising-data-flags-field-and-discovery
        
        //First, make sure the _advertising flag is initially set to false
        currently_advertising = false;

        //Create an array of 31 bytes that we will use to store our advertising data.
        //31 bytes is the maximum allowable number of bytes according to the BLE spec.
        uint8_t advertisingData[31];

        //Create a variable that stores the actual number of bytes that we are using so far
        uint8_t advertisingDataLen = 0;

        //Now, we need to place a few different pieces of information into our advertising data.

        //THE FOLLOWING LINES HAVE BEEN COMMENTED OUT
        //Reason: It seems like the ATWINC3400 is automatically inserting these bytes into the 
        //advertising data on its own. Whatever the case, I have noticed that when I insert them
        //manually using the following code, then the BLE device doesn't show up on the scanner.

        //First, let's place the appropriate flags into our advertising data
        //advertisingData[0] = 0x02;  //This packet of data will be 2-bytes long (excluding the current byte)
        //advertisingData[1] = BLEAdvertisingDataType::BLE_ADV_DATATYPE_FLAGS;
        //advertisingData[2] = BLEAdvertisingFlags::BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE | 
        //    BLEAdvertisingFlags::BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
        //advertisingDataLen += 3;

        //END OF LINES THAT HAVE BEEN COMMENTED OUT

        //Next, let's place the UUID of the advertised service into the advertising data
        if (advertised_service_uuid.str() != NULL)
        {
            int uuidLen = advertised_service_uuid.length();
            advertisingData[advertisingDataLen++] = 1 + uuidLen;
            advertisingData[advertisingDataLen++] = 
                (uuidLen > 2) ? BLEAdvertisingDataType::BLE_ADV_DATATYPE_INCOMPLETE_LIST_UUID_128BIT 
                              : BLEAdvertisingDataType::BLE_ADV_DATATYPE_INCOMPLETE_LIST_UUID_16BIT;
            memcpy(&advertisingData[advertisingDataLen], advertised_service_uuid.data(), uuidLen);
            advertisingDataLen += uuidLen;
        }

        /* 
         * The Scan response packet contains basic information about a Beacon.
         * Once an advertising packet has been received by a scanning device (such as a mobile), 
         * further information can be requested.  The Beacon responds with the Scan response packet.  
         * After sending the scan response packet (this is sent just once) the Beacon will continue 
         * broadcasting advertising packets. The package length is variable (up to 31 bytes), 
         * depending on the length of the device name.
         * Source: https://support.kontakt.io/hc/en-gb/articles/201492522-Scan-response-packet-structure
         */

        uint8_t scanResponseData[31];
        uint8_t scanResponseDataLen = 0;

        if (device_name.length() > 0) 
        {
            int localNameLen = device_name.length();

            if (localNameLen > 29) 
            {
                localNameLen = 29;
                scanResponseData[1] = 0x08;
            } 
            else 
            {
                scanResponseData[1] = 0x09;
            }

            scanResponseData[0] = 1 + localNameLen;
            memcpy(&scanResponseData[2], device_name.c_str(), localNameLen);
            scanResponseDataLen += (2 + localNameLen);
        }

        //Attempt to set the advertising and the scan response data
        at_ble_status_t at_ble_adv_data_set_result = at_ble_adv_data_set(
            advertisingData, 
            advertisingDataLen, 
            scanResponseData, 
            scanResponseDataLen);

        //Indicate that this device is a peripheral
        at_ble_set_dev_config(AT_BLE_GAP_PERIPHERAL_SLV);

        //Check to see if we were successful in doing so
        if (at_ble_adv_data_set_result != at_ble_status_t::AT_BLE_SUCCESS)
        {
            //If not, return 0
            return 0;
        }

        //Next, let's start advertising
        //TO DO: the parameters used here are simply copied from those used in the Atmel heart rate example
        //TO DO: we may need to change the parameters in the future if these are not appropriate.
        at_ble_status_t at_ble_start_status = at_ble_adv_start(
            at_ble_adv_type_t::AT_BLE_ADV_TYPE_UNDIRECTED, 
            at_ble_adv_mode_t::AT_BLE_ADV_GEN_DISCOVERABLE,
            NULL, 
            at_ble_filter_type_t::AT_BLE_ADV_FP_ANY,
            advertising_interval,
            1000,
            false
            );

        //Check to see if we successfully started advertising
        if (at_ble_start_status != at_ble_status_t::AT_BLE_SUCCESS)
        {
            //If we were not successful in our attempt to start advertising, then return 0.
            return 0;
        }        

        //Set the advertising flag equal to true
        currently_advertising = true;

        return 1;
    }

    String BLELocalDevice::GetAddress (bool include_addr_type)
    {
        at_ble_addr_t address;
        at_ble_status_t status = at_ble_addr_get(&address);
        String result = "MAC ";
        if (status == at_ble_status_t::AT_BLE_SUCCESS)
        {
            for (int i = 5; i >= 0; i--)
            {
                String t = "";
                if (address.addr[i] < 0x10)
                {
                    t += "0";
                }

                t += String(address.addr[i], HEX);

                if (i > 0)
                {
                    t += ":";
                }

                result += t;
            }
        }
        else
        {
            result += "UNKNOWN";
        }

        if (include_addr_type)
        {
            result += ", address type = ";
            switch (address.type)
            {
                case at_ble_addr_type_t::AT_BLE_ADDRESS_INVALID:
                    result += "AT_BLE_ADDRESS_INVALID";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_PUBLIC:
                    result += "AT_BLE_ADDRESS_PUBLIC";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_PRIVATE_NON_RESOLVABLE:
                    result += "AT_BLE_ADDRESS_RANDOM_PRIVATE_NON_RESOLVABLE";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_PRIVATE_RESOLVABLE:
                    result += "AT_BLE_ADDRESS_RANDOM_PRIVATE_RESOLVABLE";
                    break;
                case at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_STATIC:
                    result += "AT_BLE_ADDRESS_RANDOM_STATIC";
                    break;
                default:
                    result += "UNKNOWN";
                    break;
            }
        }

        return result;
    }

    BLELocalDevice BLE;
}