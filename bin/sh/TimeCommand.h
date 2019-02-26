#ifndef __BIN_SH_TIMECOMMAND
#define __BIN_SH_TIMECOMMAND

#include <Types.h>
#include "ShellCommand.h"

/**
 * Measure the execution time of a program.
 */
class TimeCommand : public ShellCommand
{
  public:

    /**
     * Constructor function.
     */
    TimeCommand();

    /**
     * Executes the command.
     *
     * @param nparams Number of parameters given.
     * @param params Array of parameters.
     * @return Error code or zero on success.
     */
    virtual int execute(Size nparams, char **params);
};

#endif /* __BIN_SH_TIMECOMMAND */
