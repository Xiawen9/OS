#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <Runtime.h>

int main(int argc, char **argv)
{
    dev_t dev;

    /* Verify command-line arguments. */
    if (argc < 5)
    {
	printf("usage: %s FILE TYPE MAJOR MINOR\r\n",
		argv[0]);
	return EXIT_FAILURE;
    }
    refreshMounts(0);

    /* Fill in major/minor numbers. */
    dev.major = atoi(argv[3]);
    dev.minor = atoi(argv[4]);

    /* Attempt to create the file. */
    if (mknod(argv[1], S_IFCHR, dev) < 0)
    {
	printf("%s: failed to create '%s': %s\r\n",
		argv[0], argv[1], strerror(errno));
	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
