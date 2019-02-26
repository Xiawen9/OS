#include <System.h>
#include <Types.h>
#include <errno.h>
#include "VGA.h"

VGA::VGA(Size w, Size h) : Device(BlockDeviceFile), width(w), height(h)
{
    m_identifier << "vga0";
}

Error VGA::initialize()
{
    Memory::Range range;

    // Request VGA memory
    range.size   = PAGESIZE;
    range.access = Memory::User     |
                   Memory::Readable |
                   Memory::Writable;
    range.virt   = ZERO;
    range.phys   = VGA_PADDR;
    VMCtl(SELF, Map, &range);

    // Point to the VGA mapping
    vga = (u16 *) range.virt;

    // Clear screen
    for (uint i = 0; i < width * height; i++)
    {
        vga[i] = VGA_CHAR(' ', LIGHTGREY, BLACK);
    }

    // Disable hardware cursor
    WriteByte(VGA_IOADDR, 0x0a);
    WriteByte(VGA_IODATA, 1 << 5);

    // Successfull
    return ESUCCESS;
}

Error VGA::read(IOBuffer & buffer, Size size, Size offset)
{
    if (offset + size > width * height * sizeof(u16))
    {
        return EFAULT;
    }
    buffer.write(vga + (offset / sizeof(u16)), size);
    return size;
}

Error VGA::write(IOBuffer & buffer, Size size, Size offset)
{
    if (offset + size > width * height * sizeof(u16))
    {
        return EFAULT;
    }
    memcpy(vga + (offset / sizeof(u16)), buffer.getBuffer(), size);    
    return size;
}
