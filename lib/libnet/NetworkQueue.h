#ifndef __LIBNET_NETWORKQUEUE_H
#define __LIBNET_NETWORKQUEUE_H

#include <Types.h>
#include <Index.h>

/**
 * Networking packet queue implementation.
 */
class NetworkQueue
{
  public:

    /**
     * Represents a network packet
     */
    typedef struct Packet
    {
        Size size;
        u8 *data;

        const bool operator == (const struct Packet & pkt) const
        {
            return pkt.size == size && pkt.data == data;
        }
        const bool operator != (const struct Packet & pkt) const
        {
            return pkt.size != size || pkt.data != data;
        }
    }
    Packet;

    /**
     * Constructor
     *
     * @param packetSize The size of each packet in bytes
     * @param headerSize Size of the physical header, if any
     * @param queueSize The size of the queue in number of packets
     */
    NetworkQueue(Size packetSize, Size headerSize = 0, Size queueSize = 8);

    /**
     * Destructor
     */
    virtual ~NetworkQueue();

    /**
     * Set default packet header size
     */
    void setHeaderSize(Size size);

    /**
     * Get unused packet
     */
    Packet * get();

    /**
     * Put unused packet back.
     */
    void release(Packet *packet);

    /**
     * Enqueue packet with data.
     */
    void push(Packet *packet);

    /**
     * Retrieve packet with data.
     */
    Packet * pop();

  private:

    /** Contains unused packets */
    Index<Packet> m_free;

    /** Contains packets with data */
    Index<Packet> m_data;

    /** Size of each packet */
    Size m_packetSize;

    /**
     * Size of physical hardware header.
     * This reserves some bytes at the start of
     * the actual packet payload. Some hardware needs
     * an extra physical header before the ethernet/ip headers.
     */
    Size m_packetHeader;
};

#endif /* __LIBNET_NETWORKQUEUE_H */
