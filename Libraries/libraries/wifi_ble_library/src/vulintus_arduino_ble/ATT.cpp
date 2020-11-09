#include <Arduino.h>

#include "vulintus_arduino_ble/GATT.h"
#include "vulintus_arduino_ble/local/BLELocalAttribute.h"
#include "vulintus_arduino_ble/local/BLELocalCharacteristic.h"
#include "vulintus_arduino_ble/local/BLELocalDescriptor.h"
#include "vulintus_arduino_ble/local/BLELocalService.h"
#include "vulintus_arduino_ble/remote/BLERemoteDevice.h"
#include "vulintus_arduino_ble/remote/BLERemoteService.h"
#include "vulintus_arduino_ble/BLEProperty.h"

#include "vulintus_arduino_ble/ATT.h"

#define ATT_OP_ERROR              0x01
#define ATT_OP_MTU_REQ            0x02
#define ATT_OP_MTU_RESP           0x03
#define ATT_OP_FIND_INFO_REQ      0x04
#define ATT_OP_FIND_INFO_RESP     0x05
#define ATT_OP_FIND_BY_TYPE_REQ   0x06
#define ATT_OP_FIND_BY_TYPE_RESP  0x07
#define ATT_OP_READ_BY_TYPE_REQ   0x08
#define ATT_OP_READ_BY_TYPE_RESP  0x09
#define ATT_OP_READ_REQ           0x0a
#define ATT_OP_READ_RESP          0x0b
#define ATT_OP_READ_BLOB_REQ      0x0c
#define ATT_OP_READ_BLOB_RESP     0x0d
#define ATT_OP_READ_MULTI_REQ     0x0e
#define ATT_OP_READ_MULTI_RESP    0x0f
#define ATT_OP_READ_BY_GROUP_REQ  0x10
#define ATT_OP_READ_BY_GROUP_RESP 0x11
#define ATT_OP_WRITE_REQ          0x12
#define ATT_OP_WRITE_RESP         0x13
#define ATT_OP_WRITE_CMD          0x52
#define ATT_OP_PREP_WRITE_REQ     0x16
#define ATT_OP_PREP_WRITE_RESP    0x17
#define ATT_OP_EXEC_WRITE_REQ     0x18
#define ATT_OP_EXEC_WRITE_RESP    0x19
#define ATT_OP_HANDLE_NOTIFY      0x1b
#define ATT_OP_HANDLE_IND         0x1d
#define ATT_OP_HANDLE_CNF         0x1e
#define ATT_OP_SIGNED_WRITE_CMD   0xd2

#define ATT_ECODE_INVALID_HANDLE       0x01
#define ATT_ECODE_READ_NOT_PERM        0x02
#define ATT_ECODE_WRITE_NOT_PERM       0x03
#define ATT_ECODE_INVALID_PDU          0x04
#define ATT_ECODE_AUTHENTICATION       0x05
#define ATT_ECODE_REQ_NOT_SUPP         0x06
#define ATT_ECODE_INVALID_OFFSET       0x07
#define ATT_ECODE_AUTHORIZATION        0x08
#define ATT_ECODE_PREP_QUEUE_FULL      0x09
#define ATT_ECODE_ATTR_NOT_FOUND       0x0a
#define ATT_ECODE_ATTR_NOT_LONG        0x0b
#define ATT_ECODE_INSUFF_ENCR_KEY_SIZE 0x0c
#define ATT_ECODE_INVAL_ATTR_VALUE_LEN 0x0d
#define ATT_ECODE_UNLIKELY             0x0e
#define ATT_ECODE_INSUFF_ENC           0x0f
#define ATT_ECODE_UNSUPP_GRP_TYPE      0x10
#define ATT_ECODE_INSUFF_RESOURCES     0x11

namespace VulintusArduinoBLE
{
    /// <summary>
    /// Default constructor
    /// </summary>
    ATTClass::ATTClass() :
        _maxMtu(23),
        _timeout(5000),
        _longWriteHandle(0x0000),
        _longWriteValue(NULL),
        _longWriteValueLength(0)
    {
        for (int i = 0; i < ATT_MAX_PEERS; i++) 
        {
            _peers[i].connectionHandle = 0xffff;
            _peers[i].role = 0x00;
            _peers[i].addressType = 0x00;
            memset(_peers[i].address, 0x00, sizeof(_peers[i].address));
            _peers[i].mtu = 23;
            _peers[i].device = NULL;
        }

        memset(_eventHandlers, 0x00, sizeof(_eventHandlers));
    }

    /// <summary>
    /// Destructor
    /// </summary>
    ATTClass::~ATTClass()
    {
        if (_longWriteValue) 
        {
            free(_longWriteValue);
        }
    }

    bool ATTClass::connect(uint8_t peerBdaddrType, uint8_t peerBdaddr[6])
    {
        bool isConnected = false;

        //TO DO

        return isConnected;
    }

    bool ATTClass::disconnect(uint8_t peerBdaddrType, uint8_t peerBdaddr[6])
    {
        //TO DO
        return false;
    }

    bool ATTClass::discoverAttributes(uint8_t peerBdaddrType, uint8_t peerBdaddr[6], const char* serviceUuidFilter)
    {
        //TO DO
        return true;
    }

    void ATTClass::setMaxMtu(uint16_t maxMtu)
    {
        _maxMtu = maxMtu;
    }

    void ATTClass::setTimeout(unsigned long timeout)
    {
        _timeout = timeout;
    }

    void ATTClass::addConnection(uint16_t handle, uint8_t role, uint8_t peerBdaddrType,
                        uint8_t peerBdaddr[6], uint16_t /*interval*/,
                        uint16_t /*latency*/, uint16_t /*supervisionTimeout*/,
                        uint8_t /*masterClockAccuracy*/)
    {
        //TO DO
    }

    void ATTClass::handleData(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::removeConnection(uint16_t handle, uint8_t /*reason*/)
    {
        //TO DO
    }

    uint16_t ATTClass::connectionHandle(uint8_t addressType, const uint8_t address[6]) const
    {
        //TO DO
        return 0xffff;
    }

    BLERemoteDevice* ATTClass::device(uint8_t addressType, const uint8_t address[6]) const
    {
        //TO DO
        return NULL;
    }

    bool ATTClass::connected() const
    {
        for (int i = 0; i < ATT_MAX_PEERS; i++) 
        {
            if (_peers[i].connectionHandle != 0xffff) 
            {
                return true;
            }
        }

        return false;
    }

    bool ATTClass::connected(uint8_t addressType, const uint8_t address[6]) const
    {
        return (connectionHandle(addressType, address) != 0xffff);
    }

    bool ATTClass::connected(uint16_t handle) const
    {
        //TO DO
    }

    uint16_t ATTClass::mtu(uint16_t handle) const
    {
        //TO DO
        return 23;
    }

    bool ATTClass::disconnect()
    {
        int numDisconnects = 0;

        //TO DO

        return (numDisconnects > 0);
    }

    BLEDevice ATTClass::central()
    {
        for (int i = 0; i < ATT_MAX_PEERS; i++) 
        {
            if (_peers[i].connectionHandle == 0xffff || _peers[i].role != 0x01) 
            {
                continue;
            }

            return BLEDevice(_peers[i].addressType, _peers[i].address);
        }

        return BLEDevice();
    }

    bool ATTClass::handleNotify(uint16_t handle, const uint8_t* value, int length)
    {
        int numNotifications = 0;

        //TO DO

        return (numNotifications > 0);
    }

    bool ATTClass::handleInd(uint16_t handle, const uint8_t* value, int length)
    {
        int numIndications = 0;

        //TO DO

        return (numIndications > 0);
    }

    void ATTClass::error(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::mtuReq(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    int ATTClass::mtuReq(uint16_t connectionHandle, uint16_t mtu, uint8_t responseBuffer[])
    {
        struct __attribute__ ((packed)) 
        {
            uint8_t op;
            uint16_t mtu;
        } mtuReq = { ATT_OP_MTU_REQ, mtu };

        return sendReq(connectionHandle, &mtuReq, sizeof(mtuReq), responseBuffer);
    }

    void ATTClass::mtuResp(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::findInfoReq(uint16_t connectionHandle, uint16_t mtu, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    int ATTClass::findInfoReq(uint16_t connectionHandle, uint16_t startHandle, uint16_t endHandle, uint8_t responseBuffer[])
    {
        struct __attribute__ ((packed)) 
        {
            uint8_t op;
            uint16_t startHandle;
            uint16_t endHandle;
        } findInfoReq = { ATT_OP_FIND_INFO_REQ, startHandle, endHandle };

        return sendReq(connectionHandle, &findInfoReq, sizeof(findInfoReq), responseBuffer);
    }

    void ATTClass::findInfoResp(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::findByTypeReq(uint16_t connectionHandle, uint16_t mtu, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::readByGroupReq(uint16_t connectionHandle, uint16_t mtu, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    int ATTClass::readByGroupReq(uint16_t connectionHandle, uint16_t startHandle, uint16_t endHandle, uint16_t uuid, uint8_t responseBuffer[])
    {
        //TO DO
    }

    void ATTClass::readByGroupResp(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::readOrReadBlobReq(uint16_t connectionHandle, uint16_t mtu, uint8_t opcode, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::readResp(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::readByTypeReq(uint16_t connectionHandle, uint16_t mtu, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    int ATTClass::readByTypeReq(uint16_t connectionHandle, uint16_t startHandle, uint16_t endHandle, uint16_t type, uint8_t responseBuffer[])
    {
        //TO DO
    }

    void ATTClass::readByTypeResp(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::writeReqOrCmd(uint16_t connectionHandle, uint16_t mtu, uint8_t op, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::writeResp(uint16_t connectionHandle, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::prepWriteReq(uint16_t connectionHandle, uint16_t mtu, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::execWriteReq(uint16_t connectionHandle, uint16_t mtu, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::handleNotifyOrInd(uint16_t connectionHandle, uint8_t opcode, uint8_t dlen, uint8_t data[])
    {
        //TO DO
    }

    void ATTClass::handleCnf(uint16_t /*connectionHandle*/, uint8_t /*dlen*/, uint8_t /*data*/[])
    {
        _cnf = true;
    }

    void ATTClass::sendError(uint16_t connectionHandle, uint8_t opcode, uint16_t handle, uint8_t code)
    {
        //TO DO
    }


    bool ATTClass::exchangeMtu(uint16_t connectionHandle)
    {
        //TO DO
        return true;
    }

    bool ATTClass::discoverServices(uint16_t connectionHandle, BLERemoteDevice* device, const char* serviceUuidFilter)
    {
        //TO DO
        return true;
    }

    bool ATTClass::discoverCharacteristics(uint16_t connectionHandle, BLERemoteDevice* device)
    {
        //TO DO
        return true;
    }

    bool ATTClass::discoverDescriptors(uint16_t connectionHandle, BLERemoteDevice* device)
    {
        //TO DO
        return true;
    }

    int ATTClass::sendReq(uint16_t connectionHandle, void* requestBuffer, int requestLength, uint8_t responseBuffer[])
    {
        //TO DO
        return 0;
    }

    void ATTClass::setEventHandler(BLEDeviceEvent event, BLEDeviceEventHandler eventHandler)
    {
        //TO DO
    }

    int ATTClass::readReq(uint16_t connectionHandle, uint16_t handle, uint8_t responseBuffer[])
    {
        struct __attribute__ ((packed)) 
        {
            uint8_t op;
            uint16_t handle;
        } readReq = { ATT_OP_READ_REQ, handle };

        return sendReq(connectionHandle, &readReq, sizeof(readReq), responseBuffer);
    }

    int ATTClass::writeReq(uint16_t connectionHandle, uint16_t handle, const uint8_t* data, uint8_t dataLen, uint8_t responseBuffer[])
    {
        struct __attribute__ ((packed)) 
        {
            uint8_t op;
            uint16_t handle;
            uint8_t data[255];
        } writeReq;

        writeReq.op = ATT_OP_WRITE_REQ;
        writeReq.handle = handle;
        memcpy(writeReq.data, data, dataLen);

        return sendReq(connectionHandle, &writeReq, 3 + dataLen, responseBuffer);
    }

    void ATTClass::writeCmd(uint16_t connectionHandle, uint16_t handle, const uint8_t* data, uint8_t dataLen)
    {
        struct __attribute__ ((packed)) 
        {
            uint8_t op;
            uint16_t handle;
            uint8_t data[255];
        } writeReq;

        writeReq.op = ATT_OP_WRITE_CMD;
        writeReq.handle = handle;
        memcpy(writeReq.data, data, dataLen);

        sendReq(connectionHandle, &writeReq, 3 + dataLen, NULL);
    }

    ATTClass ATT;
}

