#include <unistd.h>
#include <fcntl.h>
#include "StdioCommand.h"

StdioCommand::StdioCommand() : ShellCommand("stdio", 2)
{
    m_help = "Change standard I/O of the shell";
}

int StdioCommand::execute(Size nparams, char **params)
{
    while (true)
    {
        // Reopen standard I/O
        close(0);
        close(1);
        close(2);

        if (open(params[0], O_RDWR) >= 0 &&
            open(params[1], O_RDWR) >= 0 &&
            open(params[1], O_RDWR) >= 0)
            break;
    }
    return 0;
}
