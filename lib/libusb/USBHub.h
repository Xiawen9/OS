#ifndef __LIBUSB_USBHUB_H
#define __LIBUSB_USBHUB_H

#include <Types.h>
#include "USBDevice.h"
#include "USBDescriptor.h"

/**
 * USB Hub driver.
 */
class USBHub : public USBDevice
{
    /**
     * USB Hub standard requests.
     */
    enum RequestType
    {
        GetStatus        = 0,
        ClearFeature     = 1,
        SetFeature       = 3,
        GetDescriptor    = 6,
        SetDescriptor    = 7,
        ClearTTBuffer    = 8,
        ResetTT          = 9,
        GetTTState       = 10,
        StopTT           = 11
    };

    /**
     * USB Hub current status and changed status format.
     */
    typedef struct Status
    {
        u16 current;
        u16 changed;
    }
    Status;

    /**
     * USB Hub Port Features.
     */
    enum PortFeature
    {
        PortConnection       = 0,
        PortEnable           = 1,
        PortSuspend          = 2,
        PortOverCurrent      = 3,
        PortReset            = 4,
        PortPower            = 8,
        PortLowSpeed         = 9,
        PortClearConnection  = 16,
        PortClearEnable      = 17,
        PortClearSuspsend    = 18,
        PortClearOverCurrent = 19,
        PortClearReset       = 20,
        PortTest             = 21,
        PortIndicator        = 22
    };

  public:

    /**
     * Constructor
     */
    USBHub(u8 deviceId, const char *usbPath = "/usb");

    /**
     * Destructor
     */
    virtual ~USBHub();

    /**
     * Initialize the hub.
     *
     * @return Result code
     */
    virtual Error initialize();

  private:

    /**
     * Set feature on a HUB port.
     */
    Error setPortFeature(u8 port, PortFeature feature);

    /**
     * Attach device on port.
     */
    Error portAttach(u8 port);

    /** Hub descriptor. */
    USBDescriptor::Hub *m_hub;
};

#endif /* __LIBUSB_USBHUB_H */
