#ifndef __ARM_ARMPROCESS_H
#define __ARM_ARMPROCESS_H

#include <Process.h>

/**
 * ARM specific process implementation.
 */
class ARMProcess : public Process
{
  public:
    
    /**
     * Constructor function.
     *
     * @param id Process Identifier
     * @param entry Initial program counter value.
     * @param privileged If true, the process has unlimited access to hardware.
     */
    ARMProcess(ProcessID id, Address entry, bool privileged, const MemoryMap &map);
    
    /**
     * Destructor function.
     */
    virtual ~ARMProcess();

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
     * Allow the Process to run on the CPU.
     */
    virtual void execute(Process *previous);

  private:

};


namespace Arch
{
    typedef ARMProcess Process;
};

#endif /* __ARM_ARMPROCESS_H */
