#ifndef __KERNEL_PROCESS_MANAGER_H
#define __KERNEL_PROCESS_MANAGER_H

#include <Types.h>
#include <MemoryMap.h>
#include "Process.h"
#include "Scheduler.h"

/** Maximum number of processes. */
#define MAX_PROCS 1024

/**
 * Represents a process which may run on the host.
 */
class ProcessManager
{
  public:
    
    /**
     * Constructor function.
     */
    ProcessManager(Scheduler *scheduler);
    
    /**
     * Destructor function.
     */
    virtual ~ProcessManager();

    /**
     * Get scheduler object
     *
     * @return Scheduler object instance
     */
    Scheduler * getScheduler();

    /**
     * Create and add a new Process.
     */
    Process * create(Address entry, const MemoryMap &map);

    /**
     * Retrieve a Process by it's ID.
     * @param id ProcessID number.
     * @return Pointer to the appropriate process or ZERO if not found.
     */
    Process * get(ProcessID id);        

    /**
     * Remove a Process.
     */
    void remove(Process *proc, uint exitStatus = 0);

    /**
     * Schedule next process to run.
     */
    void schedule(Process *proc = ZERO);

    /**
     * Set the idle process.
     */
    void setIdle(Process *proc);

    /**
     * Current process running. NULL if no process running yet.
     */
    Process * current();

    /**
     * Previous process running.
     */
    Process * previous();

    /**
     * Retrieve the process table.
     * @return Pointer to the process table.
     */
    Vector<Process *> * getProcessTable();

  private:

    /** All known Processes. */
    Vector<Process *> m_procs;

    /** Object which selects processes to run. */
    Scheduler *m_scheduler;

    /** Currently executing process */
    Process *m_current;

    /** Previous process executing */
    Process *m_previous;

    /** Idle process */
    Process *m_idle;
};

/**
 * @}
 */

#endif /* __KERNEL_PROCESS_H */
