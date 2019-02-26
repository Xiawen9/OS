#include <System.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <MemoryBlock.h>
#include <NetworkClient.h>
#include <NetworkSocket.h>
#include <IPV4.h>
#include <ICMP.h>
#include <Runtime.h>
#include "NetCtl.h"

NetCtl::NetCtl(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    m_parser.setDescription("control network devices");
    //m_parser.registerPositional("DEVICE", "device name of network adapter");
    m_parser.registerPositional("ARGS", "optional key=value arguments", 0);
}

NetCtl::~NetCtl()
{
}

NetCtl::Result NetCtl::initialize()
{
    DEBUG("");
    return Success;
}

NetCtl::Result NetCtl::exec()
{
    DEBUG("");

    // Make a list of network devices
    // TODO: move this functionality to libfs's FileSystemClient
    // Get a list of mounts
    refreshMounts(0);
    FileSystemMount *mounts = ::getMounts();
    FileSystemMount *match = 0;
    Size matchLen = 0;

    // Find closest matching device
    for (Size i = 0; i < FILESYSTEM_MAXMOUNTS; i++)
    {
        if (mounts[i].path[0] && strncmp(mounts[i].path, "/network/", 9) == 0)
        {
            showDevice(mounts[i].path + 9);
        }
    }
    return Success;
}

NetCtl::Result NetCtl::showDevice(const char *deviceName)
{
    DEBUG("");
    
    String ipv4, ether, out;
    char tmp[64];

    ether << "/network/" << deviceName << "/ethernet/address";
    ipv4  << "/network/" << deviceName << "/ipv4/address";
    out   << deviceName << " ipv4 ";

    // TODO: let the libfs provide some nicer abstractions for quickly reading a String
    // from a file, maybe thru FileSystemClient or FileReader
    //

    // read the ipv4/address file
    int fd = open(*ipv4, O_RDONLY);
    int r;

    if (fd != -1)
    {
        r = read(fd, tmp, sizeof(tmp));
        if (r != -1)
        {
            tmp[r] = 0;
            out << tmp;
        }
        close(fd);
    }
    out << " ether ";

    fd = open(*ether, O_RDONLY);
    if (fd != -1)
    {
        r = read(fd, tmp, sizeof(tmp));
        if (r != -1)
        {
            tmp[r] = 0;
            out << tmp;
        }
        close(fd);
    }

    printf("%s\n", *out);
    return Success;
}
