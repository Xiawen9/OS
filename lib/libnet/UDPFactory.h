#ifndef __LIBNET_UDPFACTORY_H
#define __LIBNET_UDPFACTORY_H

#include <File.h>

class UDP;

/**
 * User Datagram Protocol (UDP).
 *
 * The UDP factory creates new sockets for applications.
 */
class UDPFactory : public File
{
  public:

    /**
     * Constructor
     */
    UDPFactory(UDP *udp);

    /**
     * Destructor
     */
    virtual ~UDPFactory();

    /**
     * Receive UDP socket information
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

  private:

    /** UDP protocol instance */
    UDP *m_udp;
};

#endif /* __LIBNET_UDPFACTORY_H */
