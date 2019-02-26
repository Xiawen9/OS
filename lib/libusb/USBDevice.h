#ifndef __LIBUSB_USBDEVICE_H
#define __LIBUSB_USBDEVICE_H

#include <System.h>
#include <Types.h>
#include <Device.h>
#include <Index.h>
#include <Array.h>
#include <Callback.h>
#include "USBTransfer.h"
#include "USBDescriptor.h"
#include "USBMessage.h"

/**
 * USB device class.
 */
class USBDevice : public Device
{
  public:

    /**
     * Constructor
     */
    USBDevice(u8 deviceId, const char *usbPath = "/usb");

    /**
     * Destructor
     */
    virtual ~USBDevice();

    /**
     * Initialize the USBDevice.
     *
     * @return Result code
     */
    virtual Error initialize();

  protected:

    /**
     * Get device descriptor.
     */
    Error getDeviceDescriptor(USBDescriptor::Device *desc,
                              Size size = sizeof(USBDescriptor::Device));

    /**
     * Get configuration descriptor.
     */
    Error getConfigDescriptor(USBDescriptor::Configuration *desc,
                              Size size = sizeof(USBDescriptor::Configuration));

    /**
     * Get interface descriptor.
     */
    Error getInterfaceDescriptor(USBDescriptor::Interface *desc);

    /**
     * Get endpoint descriptor.
     */
    Error getEndpointDescriptor(u8 endpointId, USBDescriptor::Endpoint *desc);

    /**
     * Set device address.
     */
    Error setAddress(u8 address);

    /**
     * Activate a configuration.
     */
    Error setConfiguration(u8 configId);

    /**
     * Send a control message.
     */
    Error controlMessage(u8 request,
                         const USBTransfer::Direction direction,
                         const USBTransfer::RequestType type,
                         const USBTransfer::Recipient recipient,
                         u16 value,
                         u16 index,
                         void *buffer,
                         Size size);

    /**
     * Start a synchronous USB transfer.
     */
    Error transfer(const USBTransfer::Type type,
                   const USBTransfer::Direction direction,
                   Address endpointId,
                   void *buffer,
                   Size size,
                   Size maxPacketSize = 0);

    /**
     * Start an asynchronous USB transfer
     */
    Error beginTransfer(const USBTransfer::Type type,
                        const USBTransfer::Direction direction,
                        Address endpointId,
                        void *buffer,
                        Size size,
                        Size maxPacketSize = 0,
                        CallbackFunction *callback = 0);

    /**
     * Complete asynchronous USB transfer
     */
    Error finishTransfer(FileSystemMessage *msg);

    /**
     * Submit a USB transfer to the Host controller.
     */
    Error submit(USBMessage & msg);

    /** USB device identifier. */
    Address m_id;

    /** USB speed. */
    USBTransfer::Speed m_speed;

    /** USB transfer I/O file. */
    int m_transferFile;

    /** USB bus path. */
    String m_busPath;

    /** USB device descriptor */
    USBDescriptor::Device *m_device;

    /** USB configuration descriptor. */
    USBDescriptor::Configuration *m_config;

    /** USB interface descriptors. */
    Index<USBDescriptor::Interface> m_interfaces;

    /** USB endpoint descriptors. */
    Index<USBDescriptor::Endpoint> m_endpoints;

    /** USB string descriptor */
    Index<USBDescriptor::String> m_strings;

    /**
     * Contains endpoint to saved packet id mapping.
     *
     * Some host controllers require the endpoint to save
     * the next packet identifier (Data0, Data1) for non-control transfers.
     */
    Array<u8, 128> m_endpointsPacketId;
};

#endif /* __LIBUSB_USBDEVICE_H */
