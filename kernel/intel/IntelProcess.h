#ifndef __INTEL_PROCESS_H
#define __INTEL_PROCESS_H

#include <Process.h>
#include <Types.h>

/**
 * Process which may execute on an Intel x86 CPU.
 */
class IntelProcess : public Process
{
  private:

    /** Size of the kernel stack */
    static const Size KernelStackSize = PAGESIZE;

  public:

    /**
     * Constructor function.
     *
     * @param id Process Identifier.
     * @param entry Initial EIP register value.
     * @param privileged If true, the Process has unlimited access to hardware.
     * @param map Virtual memory layout.
     */
    IntelProcess(ProcessID id, Address entry, bool privileged, const MemoryMap &map);

    /**
     * Destructor function.
     */
    virtual ~IntelProcess();

    /**
     * Initialize the Process.
     *
     * Allocates various (architecture specific) resources,
     * creates MMU context and stacks.
     *
     * @return Result code
     */
    virtual Result initialize();

    /**
     * Execute the process.
     *
     * Saves and restores registers, then perform a context switch.
     */
    virtual void execute(Process *previous);
};

namespace Arch
{
    typedef IntelProcess Process;
};

/**
 * @}
 */

#endif /* __INTEL_PROCESS_H */
