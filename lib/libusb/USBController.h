#ifndef __LIBUSB_USBCONTROLLER_H
#define __LIBUSB_USBCONTROLLER_H

#include <System.h>
#include <Types.h>
#include <DeviceServer.h>
#include <FileSystemMessage.h>
#include "USBMessage.h"

/**
 * USB controller abstract interface.
 */
class USBController : public DeviceServer
{
  public:

    /**
     * Constructor
     */
    USBController(const char *path);

    /**
     * Initialize the Controller.
     *
     * @return Result code
     */
    virtual Error initialize();

    /**
     * Submit USB transfer.
     *
     * @return Result code
     */
    virtual Error transfer(const FileSystemMessage *msg,
                           USBMessage *usb) = 0;

  protected:

    /** I/O instance */
    Arch::IO m_io;
};

#endif /* __LIBUSB_USBCONTROLLER_H */
