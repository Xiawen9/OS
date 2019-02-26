#include <System.h>
#include <Log.h>
#include "SMSC95xx.h"

SMSC95xx::SMSC95xx(u8 deviceId, const char *usbPath, NetworkServer *server)
    : NetworkDevice(server)
{
    DEBUG("");

    m_usb = new SMSC95xxUSB(deviceId, usbPath, server, this);
    m_server = server;
}

SMSC95xx::~SMSC95xx()
{
    DEBUG("");

    delete m_usb;
}

Error SMSC95xx::initialize()
{
    DEBUG("");

    m_maximumPacketSize += SMSC95xxUSB::TransmitCommandSize;
    Error r = NetworkDevice::initialize();
    if (r != ESUCCESS)
    {
        ERROR("failed to initialize NetworkDevice");
        return r;
    }

    r = m_usb->initialize();
    if (r != ESUCCESS)
    {
        ERROR("failed to initialize SMSC95xxUSB");
        return r;
    }
    return ESUCCESS;
}

Error SMSC95xx::getAddress(Ethernet::Address *address)
{
    DEBUG("");

    address->addr[0] = 0x00;
    address->addr[1] = 0x11;
    address->addr[2] = 0x22;
    address->addr[3] = 0x33;
    address->addr[4] = 0x44;
    address->addr[5] = 0x55;
    return ESUCCESS;
}

Error SMSC95xx::setAddress(Ethernet::Address *address)
{
    DEBUG("");
    return ESUCCESS;
}

Error SMSC95xx::transmit(NetworkQueue::Packet *pkt)
{
    DEBUG("");
    return m_usb->transmit(pkt);
}
