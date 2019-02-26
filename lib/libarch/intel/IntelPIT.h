#ifndef __LIBARCH_INTEL_PIT_H
#define __LIBARCH_INTEL_PIT_H

#include <Types.h>
#include <BitOperations.h>
#include <Timer.h>
#include "IntelIO.h"

/**
 * Intel 8254 Programmable Interrupt Timer (PIT).
 */
class IntelPIT : public Timer
{
  private:

    /** Oscillator frequency in hertz used by the PIT. */
    static const uint OscillatorFreq = 1193182;

    /** The IRQ vector for channel 0 is fixed to IRQ0 */
    static const uint InterruptNumber = 0;

    /**
     * Hardware registers.
     */
    enum Registers
    {
        Control      = 0x43,
        Channel0Data = 0x40
    };

    /**
     * Control Register Flags.
     */
    enum ControlFlags
    {
        Channel0      = 0,
        LatchedRead   = 0,
        AccessLowHigh = (3 << 4),
        SquareWave    = (3 << 1),
        RateGenerator = (2 << 1),
    };

  public:

    /**
     * Constructor
     */
    IntelPIT();

    /**
     * Get current timer counter.
     *
     * The timer counter is used internally by the PIT
     * to generate interrupts on the desired frequency.
     * The PIT will decrement the timer counter until 0
     * is reached, at which it will generate an interrupt
     * and restart at the initial timer counter value.
     *
     * @return Current timer counter.
     */
    uint getCounter();

    /**
     * Set interrupt frequency.
     *
     * This function configures the PIT
     * to generate interrupts on the given frequency.
     * The new frequency will be applied immediately on
     * the interrupts generated.
     *
     * @param hertz Number of interrupt triggers per second (in hertz)
     * @return Result code.
     */
    virtual Result setFrequency(Size hertz);

    /**
     * Busy wait for one trigger period.
     *
     * @return Result code.
     */
    Result waitTrigger();

  private:

    /**
     * Set Control register.
     *
     * @param flags New flags to set in the Control register.
     * @return Result code.
     */
    Result setControl(ControlFlags flags);

    /** I/O instance */
    IntelIO m_io;
};

#endif /* __LIBARCH_INTEL_PIT_H */
