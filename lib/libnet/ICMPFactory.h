#ifndef __LIBNET_ICMPFACTORY_H
#define __LIBNET_ICMPFACTORY_H

#include <File.h>
#include "ICMP.h"

class ICMP;

/**
 * Internet Control Message Protocol (ICMP) factory.
 *
 * The ICMP factory creates new sockets for applications.
 */
class ICMPFactory : public File
{
  public:

    /**
     * Constructor
     */
    ICMPFactory(ICMP *icmp);

    /**
     * Destructor
     */
    virtual ~ICMPFactory();

    /**
     * Receive ICMP response
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

  private:

    /** ICMP protocol instance */
    ICMP *m_icmp;
};

#endif /* __LIBNET_ICMPFACTORY_H */
