#include "BroadcomTimer.h"

BroadcomTimer::Result BroadcomTimer::setFrequency(Size hertz)
{
    m_cycles = BCM_SYSTIMER_FREQ / hertz;
    m_frequency = hertz;

    // Use timer slot 1. Enable.
    m_io.write(SYSTIMER_C1, m_io.read(SYSTIMER_CLO) + m_cycles);
    m_io.write(SYSTIMER_CS, m_io.read(SYSTIMER_CS) | (1 << M1));

    // Done
    return Success;
}

BroadcomTimer::Result BroadcomTimer::tick()
{
    // Increment tick counter
    m_info.ticks++;

    // Clear+acknowledge the timer interrupt
    m_io.write(SYSTIMER_CS, m_io.read(SYSTIMER_CS) | (1 << M1));
    m_io.write(SYSTIMER_C1, m_io.read(SYSTIMER_CLO) + m_cycles);

    // Done
    return Success;
}
