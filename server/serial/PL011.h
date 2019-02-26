#ifndef __ARM_RASPISERIAL_H
#define __ARM_RASPISERIAL_H

#include <API.h>
#include <System.h>
#include <Log.h>
#include <Types.h>
#include <Device.h>

class PL011 : public Device
{
  public:

    /**
     * Constructor.
     */
    PL011(u32 irq);

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

    enum {
        // The GPIO registers base address.
        GPIO_BASE = 0x200000,

        // The offsets for reach register.

        // Controls actuation of pull up/down to ALL GPIO pins.
        GPPUD = (0x94),

        // Controls actuation of pull up/down for specific GPIO pin.
        GPPUDCLK0 = (0x98),

        // The base address for UART.
        PL011_BASE = (0x1000),

        // The offsets for reach register for the UART.
        PL011_DR     = (PL011_BASE + 0x00),
        PL011_RSRECR = (PL011_BASE + 0x04),
        PL011_FR     = (PL011_BASE + 0x18),
        PL011_FR_RXFE = (1 << 4),
        PL011_FR_TXFE = (1 << 7),

        PL011_ILPR   = (PL011_BASE + 0x20),
        PL011_IBRD   = (PL011_BASE + 0x24),
        PL011_FBRD   = (PL011_BASE + 0x28),
        PL011_LCRH   = (PL011_BASE + 0x2C),
        PL011_LCRH_WLEN_8BIT = (0b11<<5),

        PL011_CR     = (PL011_BASE + 0x30),
        PL011_IFLS   = (PL011_BASE + 0x34),
        PL011_IMSC   = (PL011_BASE + 0x38),
        PL011_IMSC_RXIM = (1 << 4),
        PL011_IMSC_TXIM = (1 << 5),

        PL011_RIS    = (PL011_BASE + 0x3C),
        PL011_MIS    = (PL011_BASE + 0x40),

        PL011_MIS_RXMIS = (1 << 4),
        PL011_MIS_TXMIS = (1 << 5),

        PL011_ICR    = (PL011_BASE + 0x44),
        PL011_ICR_TXIC = (1 << 5),
        PL011_ICR_RXIC = (1 << 4),

        PL011_DMACR  = (PL011_BASE + 0x48),
        PL011_ITCR   = (PL011_BASE + 0x80),
        PL011_ITIP   = (PL011_BASE + 0x84),
        PL011_ITOP   = (PL011_BASE + 0x88),
        PL011_TDR    = (PL011_BASE + 0x8C),
    };

    /*
     * delay function
     * int32_t delay: number of cycles to delay
     *
     * This just loops <delay> times in a way that the compiler
     * wont optimize away.
     */
    void delay(s32 count);

    /** interrupt vector */
    u32 m_irq;

    /** I/O instance */
    Arch::IO m_io;
};

#endif /* __ARM_PL011_H */
