#ifndef __LIBNET_ETHERNETADDRESS_H
#define __LIBNET_ETHERNETADDRESS_H

#include <Types.h>
#include "File.h"
#include "Ethernet.h"

/**
 * Ethernet address file.
 */
class EthernetAddress : public File
{
  public:

    /**
     * Constructor
     */
    EthernetAddress(Ethernet *eth);

    /**
     * Destructor
     */
    virtual ~EthernetAddress();

    /**
     * Read Ethernet address
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /**
     * Set new Ethernet address
     *
     * @param buffer Input/Output buffer to input bytes from.
     * @param size Number of bytes to write, at maximum.
     * @param offset Offset inside the file to start writing.
     * @return Number of bytes written on success, Error on failure.
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /** Ethernet object pointer */
    Ethernet *m_eth;
};

#endif /* __LIBNET_ETHERNETADDRESS_H */
