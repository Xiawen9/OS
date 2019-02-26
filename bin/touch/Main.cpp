#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <Runtime.h>

int touch(char *prog, char *path)
{
    int ret;

    /* Attempt to creat() the file. */
    if ((ret = creat(path, S_IRUSR|S_IWUSR)) < 0)
    {
        printf("%s: failed to open '%s': %s\r\n",
                prog, path, strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
    int ret = EXIT_SUCCESS, result;

    /* Verify command-line arguments. */
    if (argc < 2)
    {
	printf("usage: %s FILE1 FILE2 ...\r\n",
		argv[0]);
	return EXIT_FAILURE;
    }
    refreshMounts(0);

    /* Touch all given files. */
    for (int i = 0; i < argc - 1; i++)
    {
	/* Perform touch. */
	result = touch(argv[0], argv[i + 1]);

	/* Update exit code if needed. */
	if (result > ret)
	{
	    ret = result;
	}
    }
    /* Done. */
    return ret;
}
