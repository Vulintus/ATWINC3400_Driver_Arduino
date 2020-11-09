/*
 *  Implementation of the ArduinoBLE API for the ATWINC3400
 *  Author: David Pruitt
 *  Date: 2 November 2020
 */

#include <Arduino.h>

extern "C" {
    #include "ble/atmel_ble_api/include/m2m_ble.h"
    #include "driver/include/m2m_periph.h"
}

#include "vulintus_arduino_ble/GAP.h"
#include "vulintus_arduino_ble/GATT.h"

#include "vulintus_arduino_ble/local/BLELocalDevice.h"

extern void wifi_cb(uint8_t u8MsgType, void *pvMsg);

namespace VulintusArduinoBLE
{
    /// <summary>
    /// Constructor
    /// </summary>
    BLELocalDevice::BLELocalDevice()
    {
        //empty
    }

    /// <summary>
    /// Destructor
    /// </summary>
    BLELocalDevice::~BLELocalDevice()
    {
        //empty
    }

    /// <summary>
    /// This method initializes the BLE stack on the ATWINC3400.
    /// Following the intilization, it then sets the default name of the BLE device
    /// to be "ATWINCBLE".
    /// </summary>
    /// <returns>M2M_SUCCESS if successful, -1 otherwise.</returns>
    int BLELocalDevice::begin()
    {
        //Set the callback method for the BLE events
        tstrWifiInitParam param;
        m2m_memset((uint8*)&param, 0, sizeof(param));
        param.pfAppWifiCb = wifi_cb;
        sint8 ble_wifi_init_result = m2m_ble_wifi_init(&param);

        //Initialize the BLE stack
        sint8 ble_init_result = m2m_ble_init();

        //Set a default device name
        if (ble_init_result == M2M_SUCCESS)
        {
            String default_device_name = "ATWINC3400BLE";
            at_ble_device_name_set((uint8_t *)default_device_name.c_str(), default_device_name.length());
        }
        
        //Return the result of the initialization process
        return ble_init_result;
    }

    /// <summary>
    /// This method effectively shuts down the BLE stack on the ATWINC3400.
    /// </summary>
    void BLELocalDevice::end()
    {
        //TO DO
    }

    void BLELocalDevice::poll()
    {
        //TO DO
    }

    void BLELocalDevice::poll(unsigned long timeout)
    {
        //TO DO
    }

    bool BLELocalDevice::connected() const
    {
        //TO DO
    }

    bool BLELocalDevice::disconnect()
    {
        //TO DO
    }

    /// <summary>
    /// Retrieves the address of the local BLE module and returns it to the
    /// caller in a string format.
    /// </summary>
    /// <returns></returns>
    String BLELocalDevice::address() const
    {
        //Grab the local address of the BLE chip from the Atmel BLE API
        at_ble_addr_t address;
        at_ble_status_t status = at_ble_addr_get(&address);

        //Put the address into a reasonable string format
        char result[18];
        sprintf(result, "%02x:%02x:%02x:%02x:%02x:%02x", 
                address.addr[5], 
                address.addr[4], 
                address.addr[3], 
                address.addr[2], 
                address.addr[1], 
                address.addr[0]);

        //Return the result to the user
        return result;        
    }

    int BLELocalDevice::rssi()
    {
        //TO DO
        return 0;
    }

    void BLELocalDevice::setAdvertisedServiceUuid(const char* advertisedServiceUuid)
    {
        GAP.setAdvertisedServiceUuid(advertisedServiceUuid);
    }

    void BLELocalDevice::setAdvertisedService(const BLEService& service)
    {
        setAdvertisedServiceUuid(service.uuid());
    }

    void BLELocalDevice::setManufacturerData(const uint8_t manufacturerData[], int manufacturerDataLength)
    {
        //TO DO
    }

    void BLELocalDevice::setManufacturerData(const uint16_t companyId, const uint8_t manufacturerData[], int manufacturerDataLength)
    {
        //TO DO
    }

    void BLELocalDevice::setLocalName(const char *localName)
    {
        GAP.setLocalName(localName);
    }

    /// <summary>
    /// Sets the name of the local BLE device, i.e. this bluetooth module.
    /// </summary>
    /// <param name="deviceName">The new device name</param>
    void BLELocalDevice::setDeviceName(const char* deviceName)
    {
        GATT.setDeviceName(deviceName);
        //at_ble_device_name_set((uint8_t *)deviceName, m2m_strlen((const uint8 *)deviceName));
    }

    void BLELocalDevice::setAppearance(uint16_t appearance)
    {
        GATT.setAppearance(appearance);
    }

    void BLELocalDevice::addService(BLEService& service)
    {
        GATT.addService(service);
    }

    int BLELocalDevice::advertise()
    {
        return GAP.advertise();
    }

    void BLELocalDevice::stopAdvertise()
    {
        return GAP.stopAdvertise();
    }

    int BLELocalDevice::scan(bool withDuplicates)
    {
        return GAP.scan(withDuplicates);
    }

    int BLELocalDevice::scanForName(String name, bool withDuplicates)
    {
        return GAP.scanForName(name, withDuplicates);
    }

    int BLELocalDevice::scanForUuid(String uuid, bool withDuplicates)
    {
        return GAP.scanForUuid(uuid, withDuplicates);
    }

    int BLELocalDevice::scanForAddress(String address, bool withDuplicates)
    {
        return GAP.scanForAddress(address, withDuplicates);
    }

    void BLELocalDevice::stopScan()
    {
        return GAP.stopScan();
    }

    BLEDevice BLELocalDevice::central()
    {
        //TO DO
        return ATT.central();
    }

    BLEDevice BLELocalDevice::available()
    {
        //TO DO
        return GAP.available();
    }

    void BLELocalDevice::setEventHandler(BLEDeviceEvent event, BLEDeviceEventHandler eventHandler)
    {
        if (event == BLEDiscovered) 
        {
            GAP.setEventHandler(event, eventHandler);
        } 
        else 
        {
            ATT.setEventHandler(event, eventHandler);
        }
    }

    void BLELocalDevice::setAdvertisingInterval(uint16_t advertisingInterval)
    {
        GAP.setAdvertisingInterval(advertisingInterval);
    }

    void BLELocalDevice::setConnectionInterval(uint16_t minimumConnectionInterval, uint16_t maximumConnectionInterval)
    {
        //TO DO
    }

    void BLELocalDevice::setConnectable(bool connectable)
    {
        GAP.setConnectable(connectable);
    }

    void BLELocalDevice::setTimeout(unsigned long timeout)
    {
        ATT.setTimeout(timeout);
    }

    void BLELocalDevice::debug(Stream& stream)
    {
        //empty
    }

    void BLELocalDevice::noDebug()
    {
        //empty
    }

    /// <summary>
    /// The singleton instance of the BLELocalDevice class.
    /// </summary>
    BLELocalDevice BLE;
}