#include <MemoryBlock.h>
#include "Timer.h"

Timer::Timer()
{
    m_frequency = 0;
    m_int       = 0;
    MemoryBlock::set(&m_info, 0, sizeof(m_info));
}

Size Timer::getInterrupt() const
{
    return m_int;
}

Size Timer::getFrequency() const
{
    return m_frequency;
}

Timer::Result Timer::setFrequency(Size hertz)
{
    m_frequency = hertz;
    return Success;
}

Timer::Result Timer::getCurrent(Info *info)
{
    info->frequency = m_frequency;
    info->ticks     = m_info.ticks;
    return Success;
}

Timer::Result Timer::initialize()
{
    return Success;
}

Timer::Result Timer::start()
{
    return Success;
}

Timer::Result Timer::stop()
{
    return Success;
}

Timer::Result Timer::tick()
{
    m_info.ticks++;
    return Success;
}

Timer::Result Timer::wait(u32 microseconds)
{
    // TODO: use getCurrent() to busy wait
    return Success;
}

bool Timer::isExpired(const Timer::Info *info)
{
    if (!info->frequency)
        return false;

    // TODO: take integer overflow into account!
    return m_info.ticks > info->ticks;
}
