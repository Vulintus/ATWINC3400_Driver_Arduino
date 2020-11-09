#include "BLEUuid.h"
#include "vulintus_arduino_ble/GAP.h"

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

namespace VulintusArduinoBLE
{
    GAPClass::GAPClass() : 
        _advertising(false),
        _scanning(false),
        _advertisedServiceUuid(NULL),
        _manufacturerData(NULL),
        _manufacturerDataLength(0),
        _localName(NULL),
        _advertisingInterval(160),
        _connectable(true),
        _serviceData(NULL),
        _serviceDataLength(0),
        _discoverEventHandler(NULL)
    {
        //empty
    }

    GAPClass::~GAPClass()
    {
        //empty
    }

    void GAPClass::setAdvertisedServiceUuid(const char* advertisedServiceUuid)
    {
        _advertisedServiceUuid = advertisedServiceUuid;
    }

    void GAPClass::setManufacturerData(const uint8_t manufacturerData[], int manufacturerDataLength)
    {
        _manufacturerData = manufacturerData;
        _manufacturerDataLength = manufacturerDataLength;
    }

    void GAPClass::setManufacturerData(const uint16_t companyId, const uint8_t manufacturerData[], int manufacturerDataLength)
    {
        uint8_t* tmpManufacturerData = (uint8_t*)malloc(manufacturerDataLength + 2);
        tmpManufacturerData[0] = companyId & 0xff;
        tmpManufacturerData[1] = companyId >> 8;
        memcpy(&tmpManufacturerData[2], manufacturerData, manufacturerDataLength);
        this->setManufacturerData(tmpManufacturerData, manufacturerDataLength + 2);
    }

    void GAPClass::setLocalName(const char *localName)
    {
        _localName = localName;
    }

    bool GAPClass::advertising()
    {
        return _advertising;
    }    

    int GAPClass::advertise()
    {
        //First, make sure the _advertising flag is initially set to false
        _advertising = false;

        //Now let's create the advertising data and the scan response data
        uint8_t advertisingData[31];
        uint8_t advertisingDataLen = 0;

        advertisingData[0] = 0x02;
        advertisingData[1] = 0x01;
        advertisingData[2] = 0x06;
        advertisingDataLen += 3;

        if (_advertisedServiceUuid) 
        {
            BLEUuid uuid(_advertisedServiceUuid);
            int uuidLen = uuid.length();

            advertisingData[advertisingDataLen++] = 1 + uuidLen;
            advertisingData[advertisingDataLen++] = (uuidLen > 2) ? 0x06 : 0x02;
            memcpy(&advertisingData[advertisingDataLen], uuid.data(), uuidLen);

            advertisingDataLen += uuidLen;
        } 
        else if (_manufacturerData && _manufacturerDataLength) 
        {
            advertisingData[advertisingDataLen++] = 1 + _manufacturerDataLength;
            advertisingData[advertisingDataLen++] = 0xff;
            memcpy(&advertisingData[advertisingDataLen], _manufacturerData, _manufacturerDataLength);

            advertisingDataLen += _manufacturerDataLength;
        }

        if (_serviceData && _serviceDataLength > 0 && advertisingDataLen >= (_serviceDataLength + 4)) 
        {
            advertisingData[advertisingDataLen++] = _serviceDataLength + 3;
            advertisingData[advertisingDataLen++] = 0x16;

            memcpy(&advertisingData[advertisingDataLen], &_serviceDataUuid, sizeof(_serviceDataUuid));
            advertisingDataLen += sizeof(_serviceDataUuid);

            memcpy(&advertisingData[advertisingDataLen],_serviceData, _serviceDataLength);
            advertisingDataLen += _serviceDataLength;
        }

        uint8_t scanResponseData[31];
        uint8_t scanResponseDataLen = 0;

        if (_localName) 
        {
            int localNameLen = strlen(_localName);

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
            memcpy(&scanResponseData[2], _localName, localNameLen);
            scanResponseDataLen += (2 + localNameLen);
        }

        //Attempt to set the advertising and the scan response data
        at_ble_status_t at_ble_adv_data_set_result = at_ble_adv_data_set(
            advertisingData, 
            advertisingDataLen, 
            scanResponseData, 
            scanResponseDataLen);

        //Check to see if we were successful in doing so
        if (at_ble_adv_data_set_result != at_ble_status_t::AT_BLE_SUCCESS)
        {
            //If not, return 0
            return 0;
        }

        //Next, let's start advertising
        //TO DO: the parameters used here are simply copied from those used in the Atmel heart rate example
        //TO DO: we may need to change the parameters to match what should actually be used here.
        at_ble_status_t at_ble_start_status = at_ble_adv_start(
            at_ble_adv_type_t::AT_BLE_ADV_TYPE_UNDIRECTED, 
            at_ble_adv_mode_t::AT_BLE_ADV_GEN_DISCOVERABLE,
            NULL, 
            at_ble_filter_type_t::AT_BLE_ADV_FP_ANY,
            _advertisingInterval,
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
        _advertising = true;

        return 1;
    }

    void GAPClass::stopAdvertise()
    {
        //Set the advertising flag to be false
        _advertising = false;

        //Make sure we are no longer advertising
        at_ble_adv_stop();
    }

    int GAPClass::scan(bool withDuplicates)
    {
        //Make sure scanning is stopped before we enable a new scan
        at_ble_scan_stop();

        //Set the scan parameters that we will be using
        uint16_t scan_interval = 0x140;     //Scan interval 60ms in steps of 625us
        uint16_t scan_window = 0x60;        //Scan window 60ms values in steps of 625ms
        uint16_t scan_timeout = 0x0000;     //Scan time-out, 0x0000 disables time-out
        at_ble_scan_type_t scan_type = at_ble_scan_type_t::AT_BLE_SCAN_ACTIVE;
        at_ble_scan_mode_t scan_mode = at_ble_scan_mode_t::AT_BLE_SCAN_GEN_DISCOVERY;

        //Now let's start a new scan
        at_ble_status_t scan_result = at_ble_scan_start(
            scan_interval, 
            scan_window, 
            scan_timeout, 
            scan_type, 
            scan_mode,
            false, 
            withDuplicates);

        //Check to see if the operation was successful
        if (scan_result != at_ble_status_t::AT_BLE_SUCCESS)
        {
            //If not, return 0
            return 0;
        }

        //If successful, then set the scan flag to true
        _scanning = true;

        //Now return a success flag to the caller.
        return 1;
    }

    int GAPClass::scanForName(String name, bool withDuplicates)
    {
        _scanNameFilter    = name;
        _scanUuidFilter    = "";
        _scanAddressFilter = "";

        return scan(withDuplicates);
    }

    int GAPClass::scanForUuid(String uuid, bool withDuplicates)
    {
        _scanNameFilter    = "";
        _scanUuidFilter    = uuid;
        _scanAddressFilter = "";

        return scan(withDuplicates);
    }

    int GAPClass::scanForAddress(String address, bool withDuplicates)
    {
        _scanNameFilter    = "";
        _scanUuidFilter    = "";
        _scanAddressFilter = address;

        return scan(withDuplicates);
    }

    void GAPClass::stopScan()
    {
        //Stop scanning
        at_ble_scan_stop();

        //Set the scanning flag to false
        _scanning = false;

        //Clear the list of discovered devices
        for (unsigned int i = 0; i < _discoveredDevices.size(); i++) 
        {
            BLEDevice* device = _discoveredDevices.get(i);
            delete device;
        }
        _discoveredDevices.clear();
    }

    BLEDevice GAPClass::available()
    {
        for (unsigned int i = 0; i < _discoveredDevices.size(); i++) 
        {
            BLEDevice* device = _discoveredDevices.get(i);

            if (device->discovered()) 
            {
                BLEDevice result = *device;
                _discoveredDevices.remove(i);
                delete device;

                if (matchesScanFilter(result)) 
                {
                    return result;
                } 
                else 
                {
                    continue;
                } 
            }
        }

        return BLEDevice();
    }

    void GAPClass::setAdvertisingInterval(uint16_t advertisingInterval)
    {
        _advertisingInterval = advertisingInterval;
    }

    void GAPClass::setConnectable(bool connectable)
    {
        _connectable = connectable;
    }

    void GAPClass::setEventHandler(BLEDeviceEvent event, BLEDeviceEventHandler eventHandler)
    {
        if (event == BLEDiscovered) 
        {
            _discoverEventHandler = eventHandler;
        }
    }

    void GAPClass::setAdvertisedServiceData(uint16_t uuid, const uint8_t data[], int length)
    {
        _serviceDataUuid = uuid;
        _serviceData = data;
        _serviceDataLength = length;
    }

    void GAPClass::handleLeAdvertisingReport(uint8_t type, uint8_t addressType, uint8_t address[6],
                            uint8_t eirLength, uint8_t eirData[], int8_t rssi)
    {
        //TO DO    
    }

    bool GAPClass::matchesScanFilter(const BLEDevice& device)
    {
        if (_scanAddressFilter.length() > 0 && !(_scanAddressFilter.equalsIgnoreCase(device.address()))) 
        {
            return false; // drop doesn't match
        } 
        else if (_scanNameFilter.length() > 0 && _scanNameFilter != device.localName()) 
        {
            return false; // drop doesn't match
        } 
        else if (_scanUuidFilter.length() > 0 && !(_scanUuidFilter.equalsIgnoreCase(device.advertisedServiceUuid()))) 
        {
            return false; // drop doesn't match
        }

        return true;
    }

    GAPClass GAP;
}

