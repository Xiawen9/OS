#include <System.h>
#include <Config.h>
#include <Macros.h>
#include <Types.h>
#include <string.h>
#include "i8250.h"

i8250::i8250(u16 b, u16 q)
    : Device(CharacterDeviceFile), base(b), irq(q)
{
    m_identifier << "serial0";
}

Error i8250::initialize()
{
#warning double IRQ claim. already done by registerInterrupt() in Main.cpp?
    /* Aquire I/O port and IRQ line permissions. */
    ProcessCtl(SELF, WatchIRQ, irq);
    ProcessCtl(SELF, EnableIRQ, irq);
    
    /* 8bit Words, no parity. */
    WriteByte(base + LINECONTROL, 3);
    
    /* Enable interrupts. */
    WriteByte(base + IRQCONTROL, 1);
    
    /* No FIFO. */
    WriteByte(base + FIFOCONTROL, 0);
    
    /* Data Ready, Request to Send. */
    WriteByte(base + MODEMCONTROL, 3);
    
    /* Set baudrate. */
    WriteByte(base + LINECONTROL, ReadByte(base + LINECONTROL) | DLAB);
    WriteByte(base + DIVISORLOW,  (11500 / BAUDRATE) & 0xff);
    WriteByte(base + DIVISORHIGH, (11500 / BAUDRATE) >> 8);
    WriteByte(base + LINECONTROL, ReadByte(base + LINECONTROL) & ~(DLAB));

    INFO("i8250 initialized");

    /* Done! */
    return ESUCCESS;
}

Error i8250::interrupt(Size vector)
{
    ProcessCtl(SELF, EnableIRQ, irq);
    return ESUCCESS;
}

Error i8250::read(IOBuffer & buffer, Size size, Size offset)
{
    Size bytes = 0;
    u8 byte;
    
    /* Read as much bytes as possible. */
    while (ReadByte(base + LINESTATUS) & RXREADY && bytes < size)
    {
        byte = ReadByte(base);
        buffer.bufferedWrite(&byte, 1);
        bytes++;
    }
    return bytes ? (Error) bytes : EAGAIN;
}

Error i8250::write(IOBuffer & buffer, Size size, Size offset)
{
    Size bytes = 0;

    /* Write as much bytes as possible. */
    while (ReadByte(base + LINESTATUS) & TXREADY && bytes < size)
    {
        WriteByte(base, buffer[bytes++]);
    }
    return bytes ? (Error) bytes : EAGAIN;
}
