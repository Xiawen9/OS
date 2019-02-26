#ifndef __SH_CHANGE_DIR_COMMAND
#define __SH_CHANGE_DIR_COMMAND

#include <Types.h>
#include "ShellCommand.h"

/**
 * Change the current working directory.
 */
class ChangeDirCommand : public ShellCommand
{
  public:
    
    /**
     * Constructor function.
     */
    ChangeDirCommand();

    /**
     * Executes the command.
     * @param nparams Number of parameters given.
     * @param params Array of parameters.
     * @return Error code or zero on success.
     */
    virtual int execute(Size nparams, char **params);
};

#endif /* __SH_CHANGE_DIR_COMMAND */
