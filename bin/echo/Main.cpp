#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int i, newline = 1, args = 1;

    for (i = 1; i < argc; i++)
    {
	if (args == 1 && strcmp(argv[i], "-n") == 0)
	{
	    newline = 0;
	    continue;
	}
	args = 0;
	printf("%s ", argv[i]);
    }
    if (newline)
	printf("\n");

    return EXIT_SUCCESS;
}
