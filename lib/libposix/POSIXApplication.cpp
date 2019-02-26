#include <Config.h>
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "POSIXApplication.h"

POSIXApplication::POSIXApplication(int argc, char **argv)
    : Application(argc, argv)
{
    m_version = VERSION;
}

POSIXApplication::~POSIXApplication()
{
}

POSIXApplication::Result POSIXApplication::output(const char *string)
{
    printf("%s", string);
    return Success;
}

void POSIXApplication::exit(int code)
{
    ::exit(code);
}
