/*
  This file is part of the ArduinoBLE library.
  Copyright (c) 2018 Arduino SA. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "vulintus_arduino_ble/ATT.h"
#include "vulintus_arduino_ble/GAP.h"
#include "vulintus_arduino_ble/HCI.h"

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
    #include "ble/atmel_ble_api/include/m2m_ble.h"
}

namespace VulintusArduinoBLE
{
    HCIClass::HCIClass()
    {
        //empty
    }

    HCIClass::~HCIClass()
    {
        //empty
    }

    void HCIClass::poll()
    {
        at_ble_events_t ble_event;
        sint8 status = m2m_ble_event_get(&ble_event, &gu8BleParam);
        if (status == AT_BLE_SUCCESS && ble_event != at_ble_events_t::AT_BLE_UNDEFINED_EVENT)
        {
            ble_event_manager(ble_event, &gu8BleParam);
        }
    }

    void HCIClass::ble_event_manager(at_ble_events_t events, void *event_params)
    {
        switch(events)
        {
            /* GAP events */
            /** Undefined event received  */
            case AT_BLE_UNDEFINED_EVENT:
                break;

            /** Scan info needs to be delivered either adv data or scan response data. \n
             * Refer to @ref at_ble_scan_info_t
             */
            case AT_BLE_SCAN_INFO:
                break;

            /** Scan report received at the end of scan period if @ref AT_BLE_SCAN_GEN_DISCOVERY or @ref AT_BLE_SCAN_LIM_DISCOVERY are used. \n
             * Refer to @ref at_ble_scan_report_t
             */
            case AT_BLE_SCAN_REPORT:
                break;

            /** Used random address. \n
             *  Refer to at_ble_rand_addr_changed_t
             */
            case AT_BLE_RAND_ADDR_CHANGED:
                break;

            /** connected to a peer device. \n
             *  Refer to at_ble_connected_t
             */
            case AT_BLE_CONNECTED:
                break;

            /** peer device connection terminated. \n
             *  Refer to at_ble_disconnected_t
             */
            case AT_BLE_DISCONNECTED:
                break;

            /** connection parameters updated. It is required to call @ref at_ble_conn_update_reply function to send response back if needed.\n
             * Refer to @ref at_ble_conn_param_update_done_t
             */
            case AT_BLE_CONN_PARAM_UPDATE_DONE:
                break;

            /** peer device asks for connection parameters update. \n
            *  Refer to at_ble_conn_param_update_request_t
            */
            case AT_BLE_CONN_PARAM_UPDATE_REQUEST:
                break;

            /** reported RX power value. \n
            *  Refer to at_ble_rx_power_value_t
            */
            case AT_BLE_RX_POWER_VALUE:
                break;

            /** Pairing procedure is completed. \n
             *  Refer to at_ble_pair_done_t
             */
            case AT_BLE_PAIR_DONE:
                break;

            /** A central device asks for Pairing. \n
             * Refer to at_ble_pair_request_t
             */
            case AT_BLE_PAIR_REQUEST:
                break;

            /** Slave security request. \n
             *  Refer to at_ble_slave_sec_request_t
             */
            case AT_BLE_SLAVE_SEC_REQUEST:
                break;

            /** A passkey or OOB data is requested as part of pairing procedure. \n
             * Refer to @ref at_ble_pair_key_request_t
             */
            case AT_BLE_PAIR_KEY_REQUEST:
                break;

            /** Encryption is requested by a master device. \n
             *  Refer to at_ble_encryption_request_t
             */
            case AT_BLE_ENCRYPTION_REQUEST:
                break;

            /** Encryption status changed. \n
             *  Refer to at_ble_encryption_status_changed_t
             */
            case AT_BLE_ENCRYPTION_STATUS_CHANGED:
                break;

            /** Resolve random address status. \n
             *  Refer to at_ble_resolv_rand_addr_status_t
             */
            case AT_BLE_RESOLV_RAND_ADDR_STATUS:
                break;

            /* GATT Client events */
            /** A primary service is found. \n
             * Refer to @ref at_ble_primary_service_found_t
             */
            case AT_BLE_PRIMARY_SERVICE_FOUND:
                break;

            /** An included service is found . \n
             * Refer to @ref at_ble_included_service_found_t
             */
            case AT_BLE_INCLUDED_SERVICE_FOUND:
                break;

            /** A Characteristic is found. \n
             * Refer to @ref at_ble_characteristic_found_t
             */
            case AT_BLE_CHARACTERISTIC_FOUND:
                break;

            /** A descriptor is found. \n
             * Refer to @ref at_ble_descriptor_found_t
             */
            case AT_BLE_DESCRIPTOR_FOUND:
                break;

            /** A discover operation has completed. \n
             * Refer to @ref at_ble_discovery_complete_t
             */
            case AT_BLE_DISCOVERY_COMPLETE:
                break;

            /** Characteristic read procedure is done. \n
             * Refer to @ref at_ble_characteristic_read_response_t
             */
            case AT_BLE_CHARACTERISTIC_READ_RESPONSE:
                break;

            /** Characteristic multiple read procedure is done. \n
             * Refer to @ref at_ble_characteristic_read_response_t
             */
            case AT_BLE_CHARACTERISTIC_READ_MULTIBLE_RESPONSE:
                break;

            /** Characteristic write procedure is done. \n
             * Refer to @ref at_ble_characteristic_write_response_t
             */
            case AT_BLE_CHARACTERISTIC_WRITE_RESPONSE:
                break;

            /** A Notification is received. \n
             * Refer to @ref at_ble_notification_received_t
             */
            case AT_BLE_NOTIFICATION_RECEIVED:
                break;

            /** An Indication is received. \n
             * Refer to @ref at_ble_indication_received_t
             */
            case AT_BLE_INDICATION_RECEIVED:
                break;

            /* GATT Server events */
            /** The peer confirmed that it has received an Indication. \n
             * Refer to @ref at_ble_indication_confirmed_t
             */
            case AT_BLE_INDICATION_CONFIRMED:
                break;

            /** The peer has changed a characteristic value. \n
             * Refer to @ref at_ble_characteristic_changed_t
             */
            case AT_BLE_CHARACTERISTIC_CHANGED:
                break;

            /** The peer has confirmed that it has received the service changed notification. \n
             * Refer to @ref at_ble_service_changed_notification_confirmed_t
             */
            case AT_BLE_SERVICE_CHANGED_NOTIFICATION_CONFIRMED:
                break;

            /** The peer asks for a write Authorization. \n
             * Refer to @ref at_ble_write_authorize_request_t
             */
            case AT_BLE_WRITE_AUTHORIZE_REQUEST:
                break;

            /** The peer asks for a read Authorization. \n
             * Refer to @ref at_ble_read_authorize_request_t
             */
            case AT_BLE_READ_AUTHORIZE_REQUEST:
                break;

            /* L2CAP events */
            /** An L2CAP packet received from a registered custom CID. \n
             * Refer to @ref at_ble_l2cap_rx_t
             */
            case AT_BLE_L2CAP_RX:
                break;

            /* Custom user defined events */
            /** A user-defined event is delivered to the system */
            case AT_BLE_CUSTOM_EVENT:
                break;

            /* Any other event */
            default:
                break;
        }
    }

    int HCIClass::readBdAddr(uint8_t addr[6])
    {
        at_ble_addr_t address;
        at_ble_status_t result_status = at_ble_addr_get(&addr);
        if (result_status == at_ble_status_t::AT_BLE_SUCCESS)
        {
            memcpy(addr, address.addr, 6);
        }

        return result_status;
    }

    int HCIClass::readRssi(uint16_t handle)
    {
        int8_t result = at_ble_rx_power_get((at_ble_handle_t)handle);
        return result;
    }

    int HCIClass::leSetRandomAddress(uint8_t addr[6])
    {
        //For more information: https://www.novelbits.io/bluetooth-address-privacy-ble/

        //Request a random static address
        at_ble_addr_t address;
        address.type = at_ble_addr_type_t::AT_BLE_ADDRESS_RANDOM_STATIC;
        at_ble_status_t result_status = at_ble_addr_set(&address);

        if (result_status == at_ble_status_t::AT_BLE_SUCCESS)
        {
            //Copy the randomly generated address into the result
            memcpy(addr, address.addr, 6);
        }

        return result_status;
    }

    int HCIClass::leCreateConn(uint16_t interval, uint16_t window, 
                                uint8_t peerBdaddrType, uint8_t peerBdaddr[6], uint8_t ownBdaddrType,
                                uint16_t minInterval, uint16_t maxInterval, uint16_t latency,
                                uint16_t supervisionTimeout, uint16_t minCeLength, uint16_t maxCeLength)
    {
        at_ble_connection_params_t connection_parameters;
        connection_parameters.ce_len_max = maxCeLength;
        connection_parameters.ce_len_min = minCeLength;
        connection_parameters.con_intv_max = maxInterval;
        connection_parameters.con_intv_min = minInterval;
        connection_parameters.con_latency = latency;
        connection_parameters.superv_to = supervisionTimeout;

        at_ble_addr_t peer;
        peer.addr = peerBdaddr;
        peer.type = (at_ble_addr_type_t) peerBdaddrType;

        at_ble_status_t result_status = at_ble_connect(&peer, 1, interval, window, &connection_parameters);
        return result_status;
    }

    int HCIClass::leCancelConn()
    {
        at_ble_status_t result_status = at_ble_connect_cancel();
        return result_status;
    }

    int HCIClass::leConnUpdate(uint16_t handle, uint16_t minInterval, uint16_t maxInterval, 
                            uint16_t latency, uint16_t supervisionTimeout)
    {
        at_ble_connection_params_t connection_parameters;
        connection_parameters.con_intv_max = maxInterval;
        connection_parameters.con_intv_min = minInterval;
        connection_parameters.con_latency = latency;
        connection_parameters.superv_to = supervisionTimeout;

        at_ble_connection_param_update((at_ble_handle_t) handle, &connection_parameters);
    }

    int HCIClass::disconnect(uint16_t handle)
    {
        at_ble_disconnect((at_ble_handle_t) handle, at_ble_disconnect_reason_t::AT_BLE_TERMINATED_BY_USER);
    }

    HCIClass HCI;
}

