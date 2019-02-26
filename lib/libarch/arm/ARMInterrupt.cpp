#include <MemoryBlock.h>
#include "ARMInterrupt.h"

extern Address vecTable[], handlerTable;

ARMInterrupt::ARMInterrupt(Address base)
{
    m_vecTable     = base;

    MemoryBlock::copy((void *)m_vecTable, vecTable, ARM_INTR_VECTAB_SIZE);
}

ARMInterrupt::Result ARMInterrupt::install(
    ARMInterrupt::Interrupt vector,
    ARMInterrupt::Handler handler)
{
    ((Address *) &handlerTable)[vector] = (Address) handler;
    return Success;
}
