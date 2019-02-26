#ifndef __LIBUSB_USBTRANSFERFILE_H
#define __LIBUSB_USBTRANSFERFILE_H

#include <File.h>
#include "USBController.h"

/**
 * USB transfer file for USBController (/usb/transfer)
 */
class USBTransferFile : public File
{
  public:

    /**
     * Constructor
     */
    USBTransferFile(USBController *controller);

    /**
     * Write bytes to the file.
     *
     * @param buffer Input/Output buffer to input bytes from.
     * @param size Number of bytes to write, at maximum.
     * @param offset Offset inside the file to start writing.
     * @return Number of bytes written on success, Error on failure.
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /** Pointer to the USB controller for doing actual transfers */
    USBController *m_controller;
};

#endif /* __LIBUSB_USBTRANSFERFILE_H */
