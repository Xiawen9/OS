#include "Application.h"

Application::Application(int argc, char **argv)
{
    m_argc = argc;
    m_argv = argv;
    m_parser.registerFlag('h', "help", "show program help");
    m_parser.registerFlag('v', "version", "show program version");
    m_parser.registerFlag('l', "log-level", "change log level");
    m_parser.registerFlag('d', "debug", "set log level to debug");
}

Application::~Application()
{
}

int Application::run()
{
    if (m_argc < 1)
        usage();
    else
        m_parser.setName(m_argv[0]);

    if (m_parser.parse(m_argc, m_argv, m_arguments) != ArgumentParser::Success)
        usage();

    // If the help argument is given, show the usage
    //if (m_arguments.get("help"))
    //    usage();

    // If the version argument is given, show version
    //if (m_arguments.get("version"))
    //    output(m_version)
    //    exit(EXIT_SUCCESS)

    //if (m_arguments.get("log-level"))
    //    Log::setMinimalLogLevel(...)

    if (m_arguments.get("debug") && Log::instance)
        Log::instance->setMinimumLogLevel(Log::Debug);

    if (initialize() != Success)
        return ExitFailure;

    if (exec() == Success)
        return ExitSuccess;
    else
        return ExitFailure;
}

void Application::usage()
{
    String & s = m_parser.getUsage();
    output(*s);
    exit(ExitFailure);
}
