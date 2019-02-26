#ifndef __HOST__
#include <System.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ARP.h>
#include <Ethernet.h>
#include <MemoryBlock.h>
#include "NetSend.h"

//
// Send manual formatted network packets:
//
//   $ netsend smsc --arp --dest=192.168.1.123
//
// Receive and dump network packets:
//
//   $ netrecv smsc
//
// Change device parameters:
//
//   $ devctl smsc ip_address=192.168.1.2 ether_address=00:11:22:33:44:55
//   $ devctl serial0 baudrate=9600
//
// Show device status and statistics:
//
//   $ devstat smsc
//   $ devstat serial0
//

NetSend::NetSend(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    m_socket = 0;

    m_parser.setDescription("send network packets");
    m_parser.registerPositional("DEVICE", "device name of network adapter");
    m_parser.registerPositional("ARGS", "optional key=value arguments", 0);
    m_parser.registerFlag('a', "arp", "send ARP packet(s)");
}

NetSend::~NetSend()
{
}

NetSend::Result NetSend::initialize()
{
    DEBUG("");

    for (HashIterator<String, Argument *> it(m_arguments.getFlags());
         it.hasCurrent(); it++)
    {
        printf("key = '%s' value = '%s'\n",
                *it.key(), *it.current()->getName());
    }
        
    for (Size i = 0; i < m_arguments.getPositionals().count(); i++)
    {
        printf("pos[%d]: %s = %s\n", i, *m_arguments.getPositionals()[i]->getName(),
                                        *m_arguments.getPositionals()[i]->getValue());
    }

    //const String *dev = m_arguments.get("device");
    //if (dev)
    //    DEBUG("sending on device: " << **dev);

    IPV4::Address ipAddr = (192 << 24) | (168 << 16) | (1 << 8) | (123);
    Ethernet::Address etherAddr;

    arpRequest(ipAddr, &etherAddr);

    return Success;
}

NetSend::Result NetSend::exec()
{
    DEBUG("");
    return Success;
}

NetSend::Result NetSend::arpRequest(IPV4::Address ipAddr,
                                    Ethernet::Address *ethAddr)
{
#ifndef __HOST__
    u8 packet[ sizeof(Ethernet::Header) +
               sizeof(ARP::Header) ];

    Ethernet::Header *ether = (Ethernet::Header *) packet;
    ARP::Header *arp = (ARP::Header *) (ether+1);

    DEBUG("");

    // Ethernet packet
    ether->source.addr[0] = 00;
    ether->source.addr[1] = 11;
    ether->source.addr[2] = 22;
    ether->source.addr[3] = 33;
    ether->source.addr[4] = 44;
    ether->source.addr[5] = 55;
    MemoryBlock::set(&ether->destination, 0xff, sizeof(Ethernet::Address));
    ether->type = cpu_to_be16(Ethernet::ARP);

    // ARP packet
    arp->hardwareType   = cpu_to_be16(ARP::Ethernet);
    arp->protocolType   = cpu_to_be16(ARP::IPV4);
    arp->hardwareLength = sizeof(Ethernet::Address);
    arp->protocolLength = sizeof(IPV4::Address);
    arp->operation      = cpu_to_be16(ARP::Request);

    MemoryBlock::copy(&arp->etherSender, &ether->source, sizeof(Ethernet::Address));
    arp->ipSender = 0xffffffff;
    MemoryBlock::copy(&arp->etherTarget, &ether->destination, sizeof(Ethernet::Address));
    arp->ipTarget = cpu_to_be32(ipAddr);;

    // Transmit on physical device
    const char *device = *m_arguments.getPositionals()[0]->getValue();
    int fd = open(device, O_RDWR);
    if (fd < 0)
    {
        printf("failed to open device '%s': %s\n", device, strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("sending on device: %s\n", device);
    Error r = write(fd, packet, sizeof(packet));
    if (r < 0)
    {
        printf("failed to send packet on device '%s': %s\n",
                device, strerror(errno));
        exit(EXIT_FAILURE);
    }
    printf("send %d bytes\n", r);
#endif
    // Done
    return Success;
}
