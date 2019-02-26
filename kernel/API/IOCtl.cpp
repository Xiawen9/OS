#include <System.h>
#include "IOCtl.h"

Error IOCtlHandler(IOOperation op, Address addr, ulong value)
{
    Arch::IO io;

    DEBUG("op =" << op << " addr=" << addr << " value=" << value);

    switch (op)
    {
        case IOByteRead:
            return io.inb(addr);

        case IOByteWrite:
            io.outb(addr, value);
            break;

        case IOWordRead:
            return io.inw(addr);
        
        case IOWordWrite:
            io.outw(addr, value);
            break;

        case IOLongWrite:
            io.outl(addr, value);
            break;
    }
    return API::Success;
}

Log & operator << (Log &log, IOOperation op)
{
    switch (op)
    {
        case IOByteRead:  log.append("IOByteRead");  break;
        case IOByteWrite: log.append("IOByteWrite"); break;
        case IOWordRead:  log.append("IOWordRead");  break;
        case IOWordWrite: log.append("IOWordWrite"); break;
        case IOLongWrite: log.append("IOLongWrite"); break;
    }
    return log;
}
