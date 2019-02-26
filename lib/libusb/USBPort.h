#ifndef __LIBUSB_USBPORT_H
#define __LIBUSB_USBPORT_H

namespace USBPort
{
    /**
     * Features which can be (un)set on a USB port.
     */
    enum Feature
    {
        Connection       = 0,
        Enable           = 1,
        Suspend          = 2,
        OverCurrent      = 3,
        Reset            = 4,
        Power            = 5,
        LowSpeed         = 6,
        ClearConnection  = 16,
        ClearEnable      = 17,
        ClearSuspend     = 18,
        ClearOverCurrent = 19,
        ClearReset       = 20,
        Test             = 21,
        Indicator        = 22
    };

    /**
     * USB Port status and status changed format.
     */
    typedef struct Status
    {
        u16 current;
        u16 changed;
    }
    Status;
};

#endif /* __LIBUSB_USBPORT_H */
