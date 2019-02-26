#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <Runtime.h>

int remove(char *prog, char *path)
{
    int ret;

    if ((ret = unlink(path)) < 0)
    {
	printf("%s: failed to unlink '%s': %s\r\n",
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

    /* Delete all given files. */
    for (int i = 0; i < argc - 1; i++)
    {
	/* Remove. */
	result = remove(argv[0], argv[i + 1]);

	/* Update exit code if needed. */
	if (result > ret)
	{
	    ret = result;
	}
    }
    /* Done. */
    return ret;
}
