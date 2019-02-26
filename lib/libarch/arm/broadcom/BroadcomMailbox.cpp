#include <System.h>
#include "BroadcomMailbox.h"

BroadcomMailbox::BroadcomMailbox()
{
}

BroadcomMailbox::Result BroadcomMailbox::initialize()
{
    // Map Mailbox registers
    if (m_io.map(IO_BASE + Base, PAGESIZE,
                 Memory::User|Memory::Readable|Memory::Writable|Memory::Device) != IO::Success)
        return IOError;

    // Initialize registers
    m_io.write(Config, 0);
    return Success;
}

BroadcomMailbox::Result BroadcomMailbox::read(
    Channel channel,
    u32 *message)
{
    // Busy wait until mailbox has data
    while (m_io.read(Status) & Empty);

    // Read message
    for (;;)
    {
        if (((*message = m_io.read(Read)) & ChannelMask) == channel)
            break;
    }
    *message &= ~(ChannelMask);
    return Success;
}

BroadcomMailbox::Result BroadcomMailbox::write(
    Channel channel,
    u32 message)
{
    // Busy wait until mailbox becomes free
    while (m_io.read(Status) & Full);

    // Write message
    m_io.write(Write, (message << 4) | channel);
    return Success;
}
