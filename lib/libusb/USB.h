#ifndef __LIBUSB_USB_H
#define __LIBUSB_USB_H

#include <Types.h>

/**
 * USB 2.0 definitions.
 */
namespace USB
{
    /**
     * USB class codes.
     */
    enum Class
    {
        InterfaceSpecific = 0x00,
        Audio             = 0x01,
        CommAndCDCControl = 0x02,
        HID               = 0x03,
        Image             = 0x06,
        Printer           = 0x07,
        MassStorage       = 0x08,
        Hub               = 0x09,
        Video             = 0x0e,                        
        WirelessControl   = 0xe0,
        Misc              = 0xef,
        VendorSpecific    = 0xff        
    };
};

#endif /* __LIBUSB_USB_H */
