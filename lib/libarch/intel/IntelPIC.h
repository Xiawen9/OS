#ifndef __LIBARCH_INTEL_PIC_H
#define __LIBARCH_INTEL_PIC_H

#include <Types.h>
#include <BitOperations.h>
#include <IntController.h>
#include "IntelIO.h"

/**
 * Intel 8259 Programmable Interrupt Controller (PIC).
 */
class IntelPIC : public IntController
{
  private:

    /**
     * Base offset for interrupt vectors from the PIC.
     *
     * External IRQ numbers 0-15 are remapped to interrupt vectors 32-47,
     * because CPU exceptions on Intel are fixed to vectors 0-17.
     */
    static const uint InterruptBase = 32;

    /** Master PIC I/O port base offset */
    static const uint MasterBase = 0x20;

    /** Slave PIC I/O port base offset */
    static const uint SlaveBase  = 0xa0;

    /**
     * Hardware registers.
     */
    enum Registers
    {
        Command = 0x0,
        Data    = 0x1
    };

    /**
     * Command Register Flags.
     */
    enum CommandFlags
    {
        Init1          = (1 << 4) | (1 << 0),
        CascadeMode    = (0),
        LevelTriggered = (0),
        Mode8086       = (1),
        EndOfInterrupt = (0x20)
    };

  public:

    /**
     * Constructor
     */
    IntelPIC();

    /**
     * Initialize the PIC.
     *
     * @return Result code.
     */
    Result initialize();

    /**
     * Enable hardware interrupt (IRQ).
     *
     * @param irq Interrupt Request number.
     * @return Result code.
     */
    virtual Result enable(uint irq);

    /**
     * Disable hardware interrupt (IRQ).
     *
     * @param irq Interrupt Request number.
     * @return Result code.
     */
    virtual Result disable(uint irq);

    /**
     * Clear hardware interrupt (IRQ).
     *
     * Clearing marks the end of an interrupt service routine
     * and causes the PIC to trigger the interrupt vector again
     * on the next trigger moment.
     *
     * @param irq Interrupt Request number to clear.
     * @return Result code.
     */
    virtual Result clear(uint irq);

  private:

    /** I/O instance for master. */
    IntelIO m_master;

    /** I/O instance for slave. */
    IntelIO m_slave;
};

#endif /* __LIBARCH_INTEL_PIC_H */
