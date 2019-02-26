#ifndef __LIBUSB_USBMESSAGE_H
#define __LIBUSB_USBMESSAGE_H

#include "USBTransfer.h"

/**
 * USB Message implementation.
 *
 * USBMessages are communicated between the
 * USBController and USBDevice classes.
 */
typedef struct USBMessage
{
    USBTransfer::Setup       setup;
    USBTransfer::Direction   direction;
    USBTransfer::Speed       speed;
    USBTransfer::Type        type;
    USBTransfer::RequestType requestType;

    Address deviceId;    /**< USB device identifier number */
    Address endpointId;  /**< USB endpoint identifier number */
    Address hubAddress;  /**< USB hub address */
    Address portAddress; /**< USB port address */
    Size maxPacketSize;  /**< Maximum packet size */
    u8 packetId;         /**< PacketId to use for non-control transfers */

    Address buffer;     /**< I/O buffer for sending/receiving payload data */
    Size size;          /**< Number of bytes to transfer. */

    /**
     * State of the USBMessage request.
     */
    enum State
    {
        Setup,
        Data,
        Status,
        Success,
        Failure
    }
    state;
}
USBMessage;

#endif /* __LIBUSB_USBMESSAGE_H */
