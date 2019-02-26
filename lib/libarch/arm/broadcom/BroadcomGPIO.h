#ifndef __LIBARCH_ARM_BROADCOMGPIO_H
#define __LIBARCH_ARM_BROADCOMGPIO_H

#include <System.h>
#include <Types.h>

/**
 * Broadcom (2835) GPIO controller implementation.
 */
class BroadcomGPIO
{
  private:

    static const Address GPIOBase = 0x200000;

    /**
     * Hardware registers.
     */
    enum Registers
    {
        FunctionSelect0 = 0
    };

  public:

    /**
     * Pin modes.
     */
    enum Mode
    {
        Input     = 0,
        Output    = 1,
        Function0 = 4,
        Function1 = 5,
        Function2 = 6,
        Function3 = 7,
        Function4 = 3,
        Function5 = 2
    };

    /**
     * Result code.
     */
    enum Result
    {
        Success,
        NotFound,
        IOError
    };

    /**
     * Constructor
     */
    BroadcomGPIO();

    /**
     * Initialize the Controller.
     *
     * @return Result code
     */
    virtual Result initialize();

    /**
     * Set alternate function.
     *
     * @param pin Pin number to set.
     * @param function Alternate function number to set.
     * @return Result code.
     */
    virtual Result setAltFunction(Size pin, uint function);

  private:

    /** I/O instance */
    Arch::IO m_io;
};

#endif /* __LIBARCH_ARM_BROADCOMGPIO_H */
