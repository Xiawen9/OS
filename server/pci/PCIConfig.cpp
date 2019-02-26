#include <File.h>
#include <FileMode.h>
#include "PCIServer.h"
#include "PCIConfig.h"

PCIConfig::PCIConfig(u16 bus, u16 slot, u16 func)
{
    this->access = OwnerRW;
    this->bus    = bus;
    this->slot   = slot;
    this->func   = func;
}

Error PCIConfig::read(IOBuffer *buffer, Size size, Size offset)
{
    Size bytes;
    ulong value = 0;

    /* Bounds checking. */
    if (offset >= 256)
    {
	return 0;
    }
    else
    {
	/* Read out the register. */
	switch (size)
	{
	    case 1:
		bytes = 1;
		value = PCI_READ_BYTE(bus, slot, func, offset);
		break;
			
	    case 2:
		bytes = 2;
		value = PCI_READ_WORD(bus, slot, func, offset);
		break;
			
	    default:
		bytes = 4;
		value = PCI_READ_LONG(bus, slot, func, offset);
		break;
	}
        /* Copy the buffers. */
	return buffer->write(&value, bytes);
    }
}
