#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "ExitCommand.h"

ExitCommand::ExitCommand()
    : ShellCommand("exit", 0)
{
    m_help = "Exit from the shell";
}


int ExitCommand::execute(Size nparams, char **params)
{
    exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
