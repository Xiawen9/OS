#include <Log.h>
#include "PrivExec.h"

Error PrivExecHandler(PrivOperation op, Address addr)
{
    ProcessManager *procs = Kernel::instance->getProcessManager();

    DEBUG("");

    switch (op)
    {
    case Idle:
        
        procs->setIdle(procs->current());
        irq_enable();

        while (true)
            idle();
    
    case Reboot:
        cpu_reboot();
        while (true) ;
        
    case Shutdown:
        cpu_shutdown();
        return API::Success;

    case WriteConsole:
        if (Log::instance)
        {
            (*Log::instance) << (char *)addr;
        }
        return API::Success;

    default:
        ;
    }
    return API::InvalidArgument;
}
