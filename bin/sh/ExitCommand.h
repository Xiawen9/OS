#ifndef __SH_EXITCOMMAND
#define __SH_EXITCOMMAND

#include <Types.h>
#include "ShellCommand.h"

/**
 * Exit the Shell.
 */
class ExitCommand : public ShellCommand
{
  public:
    
    /**
     * Constructor function.
     */
    ExitCommand();
    
    /**
     * Executes the command.
     * @param nparams Number of parameters given.
     * @param params Array of parameters.
     * @return Error code or zero on success.
     */
    virtual int execute(Size nparams, char **params);
};

#endif /* __SH_EXITCOMMAND */
