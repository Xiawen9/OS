#include <unistd.h>

unsigned int sleep(unsigned int seconds)
{
    // TODO: kernel does not support sleep/wait scheduling yet.
    // Temporary busy-loop implementation, which is inaccurate.
    for (unsigned int i = 0; i < seconds * 1000000; i++);

    return 0;
}
