/*
  This file is part of the Vulintus Arduino BLE library.
  Copyright (c) 2020 Vulintus Inc. All rights reserved.

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

extern "C"
{
    #include "ble/atmel_ble_api/include/at_ble_api.h"
}

namespace VulintusArduinoBLE
{
    ATTClass::ATTClass ()
    {
        peers = BLELinkedList<BLEPeerConnection>();
    }

    ATTClass::~ATTClass ()
    {
        //empty
    }

    void ATTClass::SendIndication (at_ble_handle_t value_handle)
    {
        for (int i = 0; i < peers.size(); i++)
        {
            at_ble_indication_send(peers.get(i).connection_handle, value_handle);
        }
    }

    void ATTClass::SendNotification (at_ble_handle_t value_handle)
    {
        for (int i = 0; i < peers.size(); i++)
        {
            at_ble_notification_send(peers.get(i).connection_handle, value_handle);
        }
    }

    BLEPeerConnection ATTClass::GetFirstPeerConnectionOrDefault ()
    {
        //Create an invalid result as the default result
        BLEPeerConnection result;
        memset(result.peer_address.addr, 0, 6);
        result.peer_address.type = at_ble_addr_type_t::AT_BLE_ADDRESS_INVALID;
        result.connection_handle = 0xffff;

        //Iterate over all existing peers
        for (int i = 0; i < peers.size(); i++)
        {
            //Get the peer
            BLEPeerConnection p = peers.get(i);

            //Make sure it has a valid connection handle
            if (p.connection_handle != 0xffff)
            {
                //Assign this peer to the result and break out of the loop
                result = p;
                break;
            }
        }

        //Return the result
        return result;
    }

    bool ATTClass::DoesConnectionExist (BLEPeerConnection connection)
    {
        bool result = false;
        for (int i = 0; i < peers.size(); i++)
        {
            BLEPeerConnection p = peers.get(i);
            if (m2m_memcmp(p.peer_address.addr, connection.peer_address.addr, 6) == 0)
            {
                result = true;
                break;
            }
        }

        return result;
    }

    void ATTClass::ProcessEvents ()
    {
        at_ble_events_t ble_event;
        sint8 status = m2m_ble_event_get(&ble_event, &gu8BleParam);
        if (status == AT_BLE_SUCCESS && ble_event != at_ble_events_t::AT_BLE_UNDEFINED_EVENT)
        {
            ble_event_manager(ble_event, &gu8BleParam);
        }
    }

    void ATTClass::ble_event_manager(at_ble_events_t events, void *event_params)
    {
        switch(events)
        {
            /* GAP events */
            /** Undefined event received  */
            case AT_BLE_UNDEFINED_EVENT:
                Serial.println("AT_BLE_UNDEFINED_EVENT");
                break;

            /** Scan info needs to be delivered either adv data or scan response data. \n
             * Refer to @ref at_ble_scan_info_t
             */
            case AT_BLE_SCAN_INFO:
                Serial.println("AT_BLE_SCAN_INFO");
                break;

            /** Scan report received at the end of scan period if @ref AT_BLE_SCAN_GEN_DISCOVERY or @ref AT_BLE_SCAN_LIM_DISCOVERY are used. \n
             * Refer to @ref at_ble_scan_report_t
             */
            case AT_BLE_SCAN_REPORT:
                Serial.println("AT_BLE_SCAN_REPORT");
                break;

            /** Used random address. \n
             *  Refer to at_ble_rand_addr_changed_t
             */
            case AT_BLE_RAND_ADDR_CHANGED:
                Serial.println("AT_BLE_RAND_ADDR_CHANGED");
                break;

            /** connected to a peer device. \n
             *  Refer to at_ble_connected_t
             */
            case AT_BLE_CONNECTED:
            {
            
                Serial.println("AT_BLE_CONNECTED");
                at_ble_connected_t connected_event_params = gu8BleParam.at_ble_connected;
                if (connected_event_params.conn_status == at_ble_status_t::AT_BLE_SUCCESS)
                {
                    //Add this new peer to our list of connected peers.
                    BLEPeerConnection p;
                    p.connection_handle = connected_event_params.handle;
                    p.peer_address = connected_event_params.peer_addr;
                    peers.add(p);
                }
            }
                
                break;

            /** peer device connection terminated. \n
             *  Refer to at_ble_disconnected_t
             */
            case AT_BLE_DISCONNECTED:
            {
                Serial.println("AT_BLE_DISCONNECTED");
                at_ble_disconnected_t disconnected_event_params = gu8BleParam.at_ble_disconnected;

                //Search for the peer that disconnected in our list of peers
                for (int i = 0; i < peers.size(); i++)
                {
                    if (peers.get(i).connection_handle == disconnected_event_params.handle)
                    {
                        //If we found the peer in the list, then remove it from the list and
                        //then break out of the loop
                        peers.remove(i);
                        break;
                    }
                }
            }
                
                break;

            /** connection parameters updated. It is required to call @ref at_ble_conn_update_reply function to send response back if needed.\n
             * Refer to @ref at_ble_conn_param_update_done_t
             */
            case AT_BLE_CONN_PARAM_UPDATE_DONE:
                Serial.println("AT_BLE_CONN_PARAM_UPDATE_DONE");
                break;

            /** peer device asks for connection parameters update. \n
            *  Refer to at_ble_conn_param_update_request_t
            */
            case AT_BLE_CONN_PARAM_UPDATE_REQUEST:
                Serial.println("AT_BLE_CONN_PARAM_UPDATE_REQUEST");
                break;

            /** reported RX power value. \n
            *  Refer to at_ble_rx_power_value_t
            */
            case AT_BLE_RX_POWER_VALUE:
                Serial.println("AT_BLE_RX_POWER_VALUE");
                break;

            /** Pairing procedure is completed. \n
             *  Refer to at_ble_pair_done_t
             */
            case AT_BLE_PAIR_DONE:
                Serial.println("AT_BLE_PAIR_DONE");
                break;

            /** A central device asks for Pairing. \n
             * Refer to at_ble_pair_request_t
             */
            case AT_BLE_PAIR_REQUEST:
                Serial.println("AT_BLE_PAIR_REQUEST");
                break;

            /** Slave security request. \n
             *  Refer to at_ble_slave_sec_request_t
             */
            case AT_BLE_SLAVE_SEC_REQUEST:
                Serial.println("AT_BLE_SLAVE_SEC_REQUEST");
                break;

            /** A passkey or OOB data is requested as part of pairing procedure. \n
             * Refer to @ref at_ble_pair_key_request_t
             */
            case AT_BLE_PAIR_KEY_REQUEST:
                Serial.println("AT_BLE_PAIR_KEY_REQUEST");
                break;

            /** Encryption is requested by a master device. \n
             *  Refer to at_ble_encryption_request_t
             */
            case AT_BLE_ENCRYPTION_REQUEST:
                Serial.println("AT_BLE_ENCRYPTION_REQUEST");
                break;

            /** Encryption status changed. \n
             *  Refer to at_ble_encryption_status_changed_t
             */
            case AT_BLE_ENCRYPTION_STATUS_CHANGED:
                Serial.println("AT_BLE_ENCRYPTION_STATUS_CHANGED");
                break;

            /** Resolve random address status. \n
             *  Refer to at_ble_resolv_rand_addr_status_t
             */
            case AT_BLE_RESOLV_RAND_ADDR_STATUS:
                Serial.println("AT_BLE_RESOLV_RAND_ADDR_STATUS");
                break;

            /* GATT Client events */
            /** A primary service is found. \n
             * Refer to @ref at_ble_primary_service_found_t
             */
            case AT_BLE_PRIMARY_SERVICE_FOUND:
                Serial.println("AT_BLE_PRIMARY_SERVICE_FOUND");
                break;

            /** An included service is found . \n
             * Refer to @ref at_ble_included_service_found_t
             */
            case AT_BLE_INCLUDED_SERVICE_FOUND:
                Serial.println("AT_BLE_INCLUDED_SERVICE_FOUND");
                break;

            /** A Characteristic is found. \n
             * Refer to @ref at_ble_characteristic_found_t
             */
            case AT_BLE_CHARACTERISTIC_FOUND:
                Serial.println("AT_BLE_CHARACTERISTIC_FOUND");
                break;

            /** A descriptor is found. \n
             * Refer to @ref at_ble_descriptor_found_t
             */
            case AT_BLE_DESCRIPTOR_FOUND:
                Serial.println("AT_BLE_DESCRIPTOR_FOUND");
                break;

            /** A discover operation has completed. \n
             * Refer to @ref at_ble_discovery_complete_t
             */
            case AT_BLE_DISCOVERY_COMPLETE:
                Serial.println("AT_BLE_DISCOVERY_COMPLETE");
                break;

            /** Characteristic read procedure is done. \n
             * Refer to @ref at_ble_characteristic_read_response_t
             */
            case AT_BLE_CHARACTERISTIC_READ_RESPONSE:
                Serial.println("AT_BLE_CHARACTERISTIC_READ_RESPONSE");
                break;

            /** Characteristic multiple read procedure is done. \n
             * Refer to @ref at_ble_characteristic_read_response_t
             */
            case AT_BLE_CHARACTERISTIC_READ_MULTIBLE_RESPONSE:
                Serial.println("AT_BLE_CHARACTERISTIC_READ_MULTIBLE_RESPONSE");
                break;

            /** Characteristic write procedure is done. \n
             * Refer to @ref at_ble_characteristic_write_response_t
             */
            case AT_BLE_CHARACTERISTIC_WRITE_RESPONSE:
                Serial.println("AT_BLE_CHARACTERISTIC_WRITE_RESPONSE");
                break;

            /** A Notification is received. \n
             * Refer to @ref at_ble_notification_received_t
             */
            case AT_BLE_NOTIFICATION_RECEIVED:
                Serial.println("AT_BLE_NOTIFICATION_RECEIVED");
                break;

            /** An Indication is received. \n
             * Refer to @ref at_ble_indication_received_t
             */
            case AT_BLE_INDICATION_RECEIVED:
                Serial.println("AT_BLE_INDICATION_RECEIVED");
                break;

            /* GATT Server events */
            /** The peer confirmed that it has received an Indication. \n
             * Refer to @ref at_ble_indication_confirmed_t
             */
            case AT_BLE_INDICATION_CONFIRMED:
                Serial.println("AT_BLE_INDICATION_CONFIRMED");
                break;

            /** The peer has changed a characteristic value. \n
             * Refer to @ref at_ble_characteristic_changed_t
             */
            case AT_BLE_CHARACTERISTIC_CHANGED:
                Serial.println("AT_BLE_CHARACTERISTIC_CHANGED");
                break;

            /** The peer has confirmed that it has received the service changed notification. \n
             * Refer to @ref at_ble_service_changed_notification_confirmed_t
             */
            case AT_BLE_SERVICE_CHANGED_NOTIFICATION_CONFIRMED:
                Serial.println("AT_BLE_SERVICE_CHANGED_NOTIFICATION_CONFIRMED");
                break;

            /** The peer asks for a write Authorization. \n
             * Refer to @ref at_ble_write_authorize_request_t
             */
            case AT_BLE_WRITE_AUTHORIZE_REQUEST:
                Serial.println("AT_BLE_WRITE_AUTHORIZE_REQUEST");
                break;

            /** The peer asks for a read Authorization. \n
             * Refer to @ref at_ble_read_authorize_request_t
             */
            case AT_BLE_READ_AUTHORIZE_REQUEST:
                Serial.println("AT_BLE_READ_AUTHORIZE_REQUEST");
                break;

            /* L2CAP events */
            /** An L2CAP packet received from a registered custom CID. \n
             * Refer to @ref at_ble_l2cap_rx_t
             */
            case AT_BLE_L2CAP_RX:
                Serial.println("AT_BLE_L2CAP_RX");
                break;

            /* Custom user defined events */
            /** A user-defined event is delivered to the system */
            case AT_BLE_CUSTOM_EVENT:
                Serial.println("AT_BLE_CUSTOM_EVENT");
                break;

            /* Any other event */
            default:
                Serial.println("DEFAULT EVENT");
                break;
        }
    }

    ATTClass ATT;
}