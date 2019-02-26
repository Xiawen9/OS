#ifndef __KERNEL_SCHEDULER_H
#define __KERNEL_SCHEDULER_H
#ifndef __ASSEMBLER__

#include <Vector.h>
#include <Macros.h>
#include "Process.h"

class Timer;

/**
 * @defgroup kernel kernel (generic)
 * @{
 */

/**
 * Responsible for deciding which Process may execute on the CPU(s).
 */
class Scheduler
{

  public:

    /**
     * Constructor function.
     */
    Scheduler();

    /**
     * Set timer to use
     *
     * @param timer Timer instance
     */
    void setTimer(Timer *timer);

    /**
     * Select the next process to run.
     */
    virtual Process * select(Vector<Process *> *procs, Process *idle);

  private:

    /** Contains last used index for scheduling */
    Size m_index;

    /** Points to the Timer to use for sleep timeouts */
    Timer *m_timer;
};

/**
 * @}
 */

#endif /* __ASSEMBLER__ */
#endif /* __KERNEL_SCHEDULER_H */
