#include "ChangeDirCommand.h"
#include <unistd.h>

ChangeDirCommand::ChangeDirCommand()
    : ShellCommand("cd", 1)
{
    m_help = "Change the current working directory";
}

int ChangeDirCommand::execute(Size nparams, char **params)
{
    return chdir(params[0]);
}
