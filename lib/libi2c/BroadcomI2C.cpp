#include <Log.h>
#include "BroadcomI2C.h"

BroadcomI2C::BroadcomI2C()
    : I2C()
{
}

BroadcomI2C::Result BroadcomI2C::initialize()
{
    // Map I2C registers
    if (m_io.map(IO_BASE + BSC1, PAGESIZE,
                 Memory::User|Memory::Readable|Memory::Writable|Memory::Device) != IO::Success)
        return IOError;

    // Initialize GPIO controller
    if (m_gpio.initialize() != BroadcomGPIO::Success)
        return IOError;

    // Set GPIO pins to ALT0 function for SDA, SCL pins
    m_gpio.setAltFunction(2, BroadcomGPIO::Function0);
    m_gpio.setAltFunction(3, BroadcomGPIO::Function0);

    // Detect I2C controller. In Qemu, the ClockDivider is always zero.
    if (m_io.read(ClockDivider) == 0)
    {        
        return NotFound;
    }

    // Set a slow clock to attempt workaround the I2C bug in Broadcom 2835
    setClockDivider(0x5dc * 3);
    DEBUG("I2C GPIO pins set");
    DEBUG("ClockDivider is " << m_io.read(ClockDivider));
    DEBUG("Status is " << m_io.read(Status));

    // Done
    return Success;
}

BroadcomI2C::Result BroadcomI2C::setAddress(Address addr)
{
    DEBUG("address is now " << addr);
    m_io.write(SlaveAddress, addr);
    return Success;
}

BroadcomI2C::Result BroadcomI2C::setClockDivider(Size divider)
{
    m_io.write(ClockDivider, divider);
    return Success;
}

BroadcomI2C::Result BroadcomI2C::write(u8 *buf, Size size)
{
    if (size > FIFOSize)
        return RangeError;

    // Clear FIFO and Status
    m_io.write(Control, ClearFIFO);
    m_io.write(Status, ClockStretchTimeout | AcknowledgeError | TransferDone);

    // Set data length
    m_io.write(DataLength, size);

    DEBUG("Writing " << size << " bytes");

    // Fill the FIFO
    for (Size i = 0; i < size; i++)
    {
        DEBUG("buf[" << i << "] = " << buf[i]);
        m_io.write(FIFO, buf[i]);
    }

    // Begin transfer
    m_io.write(Control, Enable | Transfer);

    // Wait until transfer done is set
    while (!(m_io.read(Status) & TransferDone));

    // Check status
    if (m_io.read(Status) & AcknowledgeError)
    {
        ERROR("Acknowledge error");
        return IOError;
    }
    else if (m_io.read(Status) & ClockStretchTimeout)
    {
        ERROR("ClockStretchTimeout error");
        return IOError;
    }
    // TMP: flag done? This is not documented but used in libbcm
    m_io.write(Control, m_io.read(Control) | 0x2);

    // Done
    return Success;
}

BroadcomI2C::Result BroadcomI2C::read(u8 *buf, Size size)
{
    Size count = 0;

    if (size > FIFOSize)
        return RangeError;

    // Clear FIFO and Status
    m_io.write(Control, ClearFIFO);
    m_io.write(Status, ClockStretchTimeout | AcknowledgeError | TransferDone);
    
    // Set data length
    m_io.write(DataLength, size);

    // Begin transfer
    m_io.write(Control, Enable | ReadMode | Transfer);
    DEBUG("start read " << size << " bytes");
    DEBUG("status: " << m_io.read(Status));

    // Wait until transfer done is set
    while (!(m_io.read(Status) & TransferDone));

    // Read out the whole FIFO
    while (m_io.read(Status) & RxFIFOHasData)
    {
        buf[count++] = m_io.read(FIFO);
        DEBUG("buf[" << count-1 << "]=" << buf[count-1]);
    }

    // Check status
    if (m_io.read(Status) & AcknowledgeError)
    {
        ERROR("Acknowledge error");
        return IOError;
    }
    else if (m_io.read(Status) & ClockStretchTimeout)
    {
        ERROR("ClockStretchTimeout error");
        return IOError;
    }
    // TMP: flag done? This is not documented but used in libbcm
    m_io.write(Control, m_io.read(Control) | 0x2);

    // Done
    return Success;
}
