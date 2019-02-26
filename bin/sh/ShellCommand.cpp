#include "ShellCommand.h"

ShellCommand::ShellCommand(const char *name, Size params)
{
    m_name      = name;
    m_minParams = params;
    m_help      = "";
}

ShellCommand::~ShellCommand()
{
}

const char * ShellCommand::getName() const
{
    return m_name;
}

const char * ShellCommand::getHelp() const
{
    return m_help;
}

Size ShellCommand::getMinimumParams() const
{
    return m_minParams;
}
