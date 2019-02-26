#ifndef __LIBNET_IPV4ADDRESS_H
#define __LIBNET_IPV4ADDRESS_H

#include <Types.h>
#include "File.h"
#include "IPV4.h"

/**
 * IPV4 address file.
 */
class IPV4Address : public File
{
  public:

    /**
     * Constructor
     */
    IPV4Address(IPV4 *ipv4);

    /**
     * Destructor
     */
    virtual ~IPV4Address();

    /**
     * Read IPV4 address
     *
     * @param buffer Input/Output buffer to output bytes to.
     * @param size Number of bytes to read, at maximum.
     * @param offset Offset inside the file to start reading.
     * @return Number of bytes read on success, Error on failure.
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /**
     * Set new IPV4 address
     *
     * @param buffer Input/Output buffer to input bytes from.
     * @param size Number of bytes to write, at maximum.
     * @param offset Offset inside the file to start writing.
     * @return Number of bytes written on success, Error on failure.
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /** IPV4 object pointer */
    IPV4 *m_ipv4;
};

#endif /* __LIBNET_IPV4ADDRESS_H */
