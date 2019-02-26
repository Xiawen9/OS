#include "DeviceServer.h"

DeviceServer::DeviceServer(const char *path)
    : FileSystem(path)
{
    m_interrupts.fill(ZERO);
}

DeviceServer::~DeviceServer()
{
}

Error DeviceServer::initialize()
{
    setRoot(new Directory());
    mount();
    return ESUCCESS;
}

// TODO: avoid using format strings. Replace with String.

void DeviceServer::registerDevice(Device *dev, const char *path, ...)
{
    va_list args;

    va_start(args, path);
    FileSystem::registerFile(dev, path, args);
    va_end(args);

    // Add to the list of Devices
    m_devices.insert(dev);

    // Initialize the device
    dev->initialize();
}

void DeviceServer::registerInterrupt(Device *dev, Size vector)
{
    if (!m_interrupts[vector])
    {
        m_interrupts.insert(vector, new List<Device *>);
    }
    m_interrupts[vector]->append(dev);

    // Register to kernel
    ProcessCtl(SELF, WatchIRQ, vector);
    ProcessCtl(SELF, EnableIRQ, vector);

    // Register interrupt handler
    addIRQHandler(vector, (IRQHandlerFunction) &DeviceServer::interruptHandler);
}

void DeviceServer::interruptHandler(Size vector)
{
    List<Device *> *lst = m_interrupts.at(vector);

    // Do we have any Devices with this interrupt vector?
    if (lst)
    {
        // Loop all Devices of interest. Invoke callback.
        for (ListIterator<Device *> i(lst); i.hasCurrent(); i++)
        {
            i.current()->interrupt(vector);
        }
    }
    // Keep retrying any pending requests, if any
    while (retryRequests());
}
