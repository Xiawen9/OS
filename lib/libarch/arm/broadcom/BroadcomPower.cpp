// TODO: it may be possible to implement power management using a /power DeviceServer.

#include <Log.h>
#include "BroadcomPower.h"

BroadcomPower::BroadcomPower()
{
    m_mask = UART0;
}

BroadcomPower::Result BroadcomPower::initialize()
{
    // Initialize mailbox
    if (m_mailbox.initialize() != BroadcomMailbox::Success)
    {
        ERROR("failed to initialize mailbox");
        return IOError;
    }
    // Initialize register stats
    m_mailbox.write(BroadcomMailbox::PowerManagement, m_mask);
    return Success;
}

BroadcomPower::Result BroadcomPower::enable(BroadcomPower::Device device)
{
    m_mask |= device;
    m_mailbox.write(BroadcomMailbox::PowerManagement, m_mask);
    m_mailbox.read(BroadcomMailbox::PowerManagement, &m_mask);
    return Success;
}
