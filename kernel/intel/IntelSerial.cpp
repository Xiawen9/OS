#include <System.h>
#include "IntelSerial.h"

IntelSerial::IntelSerial(u16 base)
{
    m_io.setBase(base);

    /* 8bit Words, no parity. */
    m_io.outb(LINECONTROL, 3);
    
    /* Enable interrupts. */
    m_io.outb(IRQCONTROL, 1);
    
    /* No FIFO. */
    m_io.outb(FIFOCONTROL, 0);
    
    /* Data Ready, Request to Send. */
    m_io.outb(MODEMCONTROL, 3);
    
    /* Set baudrate. */
    m_io.outb(LINECONTROL, m_io.inb(LINECONTROL) | DLAB);
    m_io.outb(DIVISORLOW,  (11500 / BAUDRATE) & 0xff);
    m_io.outb(DIVISORHIGH, (11500 / BAUDRATE) >> 8);
    m_io.outb(LINECONTROL, m_io.inb(LINECONTROL) & ~DLAB);
}

void IntelSerial::write(const char *str)
{
    /* Write as much bytes as possible. */
    while (m_io.inb(LINESTATUS) & TXREADY && *str)
    {
        m_io.outb(TRANSMIT, *str++);
    }
}
