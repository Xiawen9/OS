#include <Log.h>
#include "BroadcomGPIO.h"

BroadcomGPIO::BroadcomGPIO()
{
}

BroadcomGPIO::Result BroadcomGPIO::initialize()
{
    if (m_io.map(IO_BASE + GPIOBase, PAGESIZE,
                 Memory::User|Memory::Readable|Memory::Writable|Memory::Device)
        != IO::Success)
        return IOError;

    return Success;
}

BroadcomGPIO::Result BroadcomGPIO::setAltFunction(Size pin, uint function)
{
    // pin is a BCM2835 GPIO pin number NOT RPi pin number
    //
    // There are 6 control registers, each control the functions of a block
    // of 10 pins.
    // Each control register has 10 sets of 3 bits per GPIO pin:
    //
    //    000 = GPIO Pin X is an input
    //    001 = GPIO Pin X is an output
    //    100 = GPIO Pin X takes alternate function 0
    //    101 = GPIO Pin X takes alternate function 1
    //    110 = GPIO Pin X takes alternate function 2
    //    111 = GPIO Pin X takes alternate function 3
    //    011 = GPIO Pin X takes alternate function 4
    //    010 = GPIO Pin X takes alternate function 5
    //
    uint shift = (pin % 10) * 3;
#warning dont use set(). use a mask instead.
#warning dont add pin/10. we must be 4-byte aligned when writing (32-bit)
    m_io.set(FunctionSelect0 + (pin / 10),
             function << shift);
    return Success;
}
