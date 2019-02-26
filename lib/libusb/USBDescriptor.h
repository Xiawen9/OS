#ifndef __LIBUSB_USBDESCRIPTOR_H
#define __LIBUSB_USBDESCRIPTOR_H

#include <Types.h>

namespace USBDescriptor
{
    /**
     * USB Descriptor Types.
     */
    enum Type
    {
        DeviceType        = 1,
        ConfigurationType = 2,
        StringType        = 3,
        InterfaceType     = 4,
        EndpointType      = 5,
        HubType           = 0x29
    };

    /**
     * USB Device Descriptor.
     */
    typedef struct Device
    {
        u8  length;
        u8  descriptorType;
        u16 bcdUSB;
        u8  deviceClass;
        u8  deviceSubClass;
        u8  deviceProtocol;
        u8  maxPacketSize;
        u16 vendorId;
        u16 productId;
        u16 bcdDevice; // TODO: what is this?
        u8  manufacturer;
        u8  product;
        u8  serialNumber;
        u8  numConfigurations;
    }
    PACKED Device;

    /**
     * USB Configuration Descriptor.
     */
    typedef struct Configuration
    {
        u8  length;
        u8  descriptorType;
        u16 totalLength;
        u8  numInterfaces;
        u8  configurationValue;
        u8  configuration;
        u8  attributes;
        u8  maxPower;
    }
    PACKED Configuration;

    /**
     * USB Interface Descriptor.
     */
    typedef struct Interface
    {
        u8 length;
        u8 descriptorType;
        u8 interfaceNumber;
        u8 alternateSetting;
        u8 numEndpoints;
        u8 interfaceClass;
        u8 interfaceSubClass;
        u8 interfaceProtocol;
        u8 interface;

        // TODO: please fix libstd, such that this is not needed anymore.
        bool operator == (const struct Interface & ep) const {
            return ep.descriptorType == descriptorType;
        }
        bool operator != (const struct Interface & ep) const {
            return ep.descriptorType != descriptorType;
        }

    }
    PACKED Interface;

    /**
     * USB Endpoint Descriptor.
     */
    typedef struct Endpoint
    {
        u8  length;
        u8  descriptorType;
        u8  endpointAddress; /** @note: low 7 bits are the address, followed by direction (1 bit) */
        u8  attributes;
        u16 maxPacketSize;
        u8  interval;

        // TODO: please fix libstd, such that this is not needed anymore.
        bool operator == (const struct Endpoint & ep) const {
            return ep.descriptorType == descriptorType;
        }
        bool operator != (const struct Endpoint & ep) const {
            return ep.descriptorType != descriptorType;
        }
    }
    PACKED Endpoint;

    /**
     * USB Hub Descriptor.
     */
    typedef struct Hub
    {
        u8  descLength;
        u8  descriptorType;
        u8  numPorts;
        u16 hubCharacteristics;
        u8  pwrOn2PwrGood;
        u8  hubContrCurrent;
        u8  varData[64];
    }
    PACKED Hub;

    /**
     * USB String Descriptor
     */
    typedef struct String
    {
        u8  length;
        u8  descriptorType;
        u16 string[];

        // TODO: please fix libstd, such that this is not needed anymore.
        bool operator == (const struct String & ep) const {
            return ep.descriptorType == descriptorType;
        }
        bool operator != (const struct String & ep) const {
            return ep.descriptorType != descriptorType;
        }

    }
    PACKED String;
};

#endif /* __LIBUSB_USBDESCRIPTOR_H */
