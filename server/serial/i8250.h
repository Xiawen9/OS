#ifndef __SERIAL_I8250_H
#define __SERIAL_I8250_H
        
/**  
 * @defgroup i8250 i8250 (Intel 8250)
 * @{    
 */

#include <Macros.h>
#include <Types.h>
#include <Device.h>


/**
 * i8250 serial UART.
 */
class i8250 : public Device
{
  public:

    /**
     * Constants used to communicate with the UART.
     */
    enum Constants
    {
        TRANSMIT     = 0,
        RECEIVE      = 0,
        DIVISORLOW   = 0,
        DIVISORHIGH  = 1,
        RXREADY      = 1,
        IRQCONTROL   = 1,
        IRQSTATUS    = 2,
        FIFOCONTROL  = 2,
        LINECONTROL  = 3,
        MODEMCONTROL = 4,
        LINESTATUS   = 5,
        TXREADY      = 0x20,
        DLAB         = 0x80,
        BAUDRATE     = 9600,
    };

    /**
     * Constructor function.
     * @param base I/O base port.
     */
    i8250(u16 base, u16 irq);

    /**
     * @brief Initializes the i8250 serial UART.
     * @return Error status code.
     */
    virtual Error initialize();

    /**
     * Called when an interrupt has been triggered for this device.
     * @param vector Vector number of the interrupt.
     * @return Error result code.
     */
    virtual Error interrupt(Size vector);

    /** 
     * Read bytes from the i8250.
     * @param buffer Buffer to save the read bytes.
     * @param size Number of bytes to read.
     * @param offset Unused.
     * @return Number of bytes on success and ZERO on failure. 
     */
    virtual Error read(IOBuffer & buffer, Size size, Size offset);

    /** 
     * Write bytes to the device.
     * @param buffer Buffer containing bytes to write. 
     * @param size Number of bytes to write.
     * @param offset Unused.
     * @return Number of bytes on success and ZERO on failure. 
     */
    virtual Error write(IOBuffer & buffer, Size size, Size offset);

  private:

    /** Base I/O port. */
    u16 base;
    
    /** Interrupt vector. */
    u16 irq;
};

/**
 * @}
 */

#endif /* __SERIAL_I8250_H */
