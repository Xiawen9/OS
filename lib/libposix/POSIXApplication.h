#ifndef __LIBPOSIX_POSIXAPPLICATION_H
#define __LIBPOSIX_POSIXAPPLICATION_H

#include <Application.h>

/**
 * POSIX-compatible application
 */
class POSIXApplication : public Application
{
  public:

    /**
     * Class constructor.
     */
    POSIXApplication(int argc, char **argv);

    /**
     * Class destructor.
     */
    virtual ~POSIXApplication();

  protected:

    /**
     * Print text to output.
     *
     * @param string Text to print to program output.
     * @return Result code.
     */
    virtual Result output(const char *string);

    /**
     * Terminate program.
     *
     * @param code Termination code.
     */
    virtual void exit(int code);
};

#endif /* __LIBPOSIX_POSIXAPPLICATION_H */
