#include <File.h>
#include <FileMode.h>
#include "PCIServer.h"
#include "PCIRegister.h"

PCIRegister::PCIRegister(u16 bus, u16 slot, u16 func, u16 reg, Size size)
{
    this->access = OwnerRW;
    this->bus    = bus;
    this->slot   = slot;
    this->func   = func;
    this->reg    = reg;
    this->size   = size;
}

Error PCIRegister::read(IOBuffer *buffer, Size size, Size offset)
{
    char buf[32];
    ulong value = 0;
    Size bytes;
	
    /* Bounds checking. */
    if (offset >= this->size)
    {
	return 0;
    }
    else
    {
	/* Read out the register. */
	switch (this->size)
	{
	    case 1:
		value = PCI_READ_BYTE(bus, slot, func, reg);
		break;
			
	    case 2:
		value = PCI_READ_WORD(bus, slot, func, reg);
		break;
			
	    default:
		value = PCI_READ_LONG(bus, slot, func, reg);
		break;
	}
	itoa(buf, 16, value);
	
	/* How much bytes to copy? */
	bytes = strlen(buf) + 1;

	if (bytes > size)
	    bytes = size;
        
        /* Copy the buffers. */
	return buffer->write(buf + offset, bytes);
    }
}
