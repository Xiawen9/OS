#ifndef __LIBNET_ARP_H
#define __LIBNET_ARP_H

#include <Types.h>
#include <HashTable.h>
#include "Ethernet.h"
#include "IPV4.h"
#include "NetworkProtocol.h"

class ARPSocket;

/**
 * Address Resolution Protocol
 */
class ARP : public NetworkProtocol
{
  private:

    static const Size MaxRetries = 3;

    typedef struct ARPCache
    {
        Ethernet::Address ethAddr;
        Timer::Info time;
        Size retryCount;
        bool valid;
    }
    ARPCache;

  public:

    /**
     * ARP hardware types
     */
    enum HardwareType
    {
        Ethernet = 1
    };

    /**
     * ARP inter-network protocol types.
     */
    enum ProtocolType
    {
        IPV4 = 0x0800
    };

    /**
     * ARP message types (operation codes)
     */
    enum Operation
    {
        Request = 1,
        Reply   = 2
    };

    /**
     * ARP network packet header.
     *
     * This header is prepended to every
     * ARP packet send on the actual physical link.
     */
    typedef struct Header
    {
        u16 hardwareType;
        u16 protocolType;
        u8  hardwareLength;
        u8  protocolLength;
        u16 operation;

        Ethernet::Address etherSender;
        IPV4::Address     ipSender;

        Ethernet::Address etherTarget;
        IPV4::Address     ipTarget;
    }
    PACKED Header;

    /**
     * Constructor
     */
    ARP(NetworkServer *server,
        NetworkDevice *device);

    /**
     * Destructor
     */
    virtual ~ARP();

    /**
     * Perform initialization.
     */
    virtual Error initialize();

    /**
     * Set IPV4 instance
     *
     * @param ip IPV4 instance
     */
    void setIP(::IPV4 *ip);

    void setEthernet(::Ethernet *ether);

    /**
     * Lookup Ethernet address for an IP
     *
     * @param ipAddr Input IP address to lookup
     * @param ethAddr Output Ethernet address when found
     * @return EAGAIN when the lookup is in progress
     *         ESUCCESS on success
     *         Other error code on error
     */
    Error lookupAddress(IPV4::Address *ipAddr,
                        Ethernet::Address *ethAddr);

    /**
     * Send ARP request
     *
     * @param address IPV4 address to lookup
     */
    Error sendRequest(IPV4::Address address);

    /**
     * Send ARP reply
     *
     * @param ethaddr Ethernet address to send reply to
     * @param ipaddr IP address of the origin
     */
    Error sendReply(const Ethernet::Address *ethaddr,
                    const IPV4::Address ipAddr);

    /**
     * Process incoming network packet.
     *
     * @return Error code
     */
    virtual Error process(NetworkQueue::Packet *pkt, Size offset);

  private:

    /**
     * Insert a new entry to the ARP cache
     *
     * @param ipAddr IP address to add
     * @return ARPCache object pointer
     */
    ARPCache * insertCacheEntry(IPV4::Address ipAddr);

    /**
     * Retrieve cache entry by IP
     *
     * @param ipAddr IP address to lookup
     * @return ARPCache object pointer or ZERO if not found
     */
    ARPCache * getCacheEntry(IPV4::Address ipAddr);

    /**
     * Update cache entry
     *
     * @param ipAddr IP address for update
     * @param ethAddr Ethernet address for update
     */
    void updateCacheEntry(IPV4::Address ipAddr,
                          Ethernet::Address ethAddr);

    /** The single ARP socket */
    ARPSocket *m_sock;

    /** IPV4 instance object */
    ::IPV4 *m_ip;

    /** Ethernet instance */
    ::Ethernet *m_ether;

    /** Contains a cached mapping from IP to Ethernet addresses */
    HashTable<IPV4::Address, ARPCache *> m_cache;
};

#endif /* __LIBNET_ARP_H */
