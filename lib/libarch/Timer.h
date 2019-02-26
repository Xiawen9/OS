#ifndef __LIBARCH_TIMER_H
#define __LIBARCH_TIMER_H

#include <Macros.h>
#include <Types.h>

/**
 * Represents a configurable timer device.
 */
class Timer
{
  private:

  public:

    /**
     * Timer information structure.
     */
    typedef struct Info
    {
        u64 ticks;
        Size frequency;
    }
    Info;

    /**
     * Result codes.
     */
    enum Result
    {
        Success,
        NotFound,
        IOError,
        InvalidFrequency
    };

    /**
     * Constructor
     */
    Timer();

    /**
     * Get timer interrupt number.
     *
     * @return Interrupt number.
     */
    Size getInterrupt() const;

    /**
     * Get timer frequency.
     *
     * @return Frequency of the timer in hertz.
     */
    Size getFrequency() const;

    /**
     * Set timer frequency.
     *
     * @param hertz Frequency of the timer in hertz.
     * @return Result code.
     */
    virtual Result setFrequency(Size hertz);

    /**
     * Get current timer info.
     *
     * @param info Timer Info object pointer for output.
     * @return Result code.
     */
    virtual Result getCurrent(Info *info);

    /**
     * Initialize the timer.
     *
     * @return Result code.
     */
    virtual Result initialize();

    /**
     * Start the timer.
     *
     * This function lets the timer run. The timer
     * will generate interrupts on the configured frequency.
     *
     * @return Result code.
     */
    virtual Result start();

    /**
     * Stop the timer.
     *
     * This function brings the timer to a halt. The timer
     * will not generate any interrupts.
     *
     * @return Result code.
     */
    virtual Result stop();

    /**
     * Process timer tick.
     *
     * Should be called on each Timer interrupt to
     * keep the m_info variable synchronized with the actual hardware.
     */
    virtual Result tick();

    /**
     * Busy wait a number of microseconds.
     *
     * @param microseconds The number of microseconds to wait at minimum.
     * @return Result code.
     */
    virtual Result wait(u32 microseconds);

    /**
     * Check if a timer value is expired
     *
     * @param info Timer info value to compare
     * @return True if expired, false otherwise
     */
    bool isExpired(const Info *info);

  protected:

    /** The current Timer information. */
    Info m_info;

    /** Frequency of the Timer. */
    Size m_frequency;

    /** Timer interrupt number. */
    Size m_int;
};

#endif /* __LIBARCH_TIMER_H */
