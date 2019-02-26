#include <stdio.h>
#include <HashIterator.h>
#include "HelpCommand.h"
#include "ShellCommand.h"
#include "Shell.h"

HelpCommand::HelpCommand(Shell *shell)
    : ShellCommand("help", 0)
{
    m_shell = shell;
    m_help  = "Print the help message";
}

int HelpCommand::execute(Size nparams, char **params)
{
    printf("List of builtin Shell commands:\r\n\r\n");

    for (HashIterator<String, ShellCommand *> i(m_shell->getCommands()); i.hasCurrent(); i++)
    {
        printf("%s -- %s\r\n", i.current()->getName(), i.current()->getHelp());
    }
    printf("\r\n");
    printf("Type 'ls /bin' to see available user commands\r\n");

    return 0;
}
