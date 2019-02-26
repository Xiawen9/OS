#ifndef __LIBNET_SMSC95XX_H
#define __LIBNET_SMSC95XX_H

#include <NetworkDevice.h>
#include "SMSC95xxUSB.h"

/**
 * SMSC95xx USB-based Ethernet controller.
 */
class SMSC95xx : public NetworkDevice
{
  private:

  public:

    /**
     * Constructor
     */
    SMSC95xx(u8 deviceId, const char *usbPath, NetworkServer *server);

    /**
     * Destructor
     */
    virtual ~SMSC95xx();

    /**
     * Initialize the controller.
     *
     * @return Result code
     */
    virtual Error initialize();

    /**
     * Read ethernet address.
     *
     * @param address Ethernet address reference for output
     * @return Error code
     */
    virtual Error getAddress(Ethernet::Address *address);

    /**
     * Set ethernet address
     *
     * @param address New ethernet address to set
     * @return Error code
     */
    virtual Error setAddress(Ethernet::Address *address);

    /**
     * Transmit one network packet
     *
     * @param pkt Network packet buffer
     */
    virtual Error transmit(NetworkQueue::Packet *pkt);

  private:

    /** USB enabled implementation class */
    SMSC95xxUSB *m_usb;
};

#endif /* __LIBNET_SMSC95XX_H */
