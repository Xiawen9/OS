#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <TerminalCodes.h>
#include <Runtime.h>

int main(int argc, char **argv)
{
    DIR *d;
    struct dirent *dent;
    struct stat st;
    char path[255], tmp[255];

    /* Grab command-line arguments, if any */
    if (argc > 1)
    {
	strncpy(path, argv[1], sizeof(path));
	path[sizeof(path) - 1] = 0;
    }
    else
	getcwd(path, sizeof(path));

    refreshMounts(0);

    /* Attempt to open the directory. */
    if (!(d = opendir(path)))
    {
	printf("%s: failed to open '%s': %s\r\n",
		argv[0], path, strerror(errno));
	return EXIT_FAILURE;
    }
    /* Read directory. */
    while ((dent = readdir(d)))
    {
	/* Coloring. */
	switch (dent->d_type)
	{
	    case DT_DIR:
		printf("%s", BLUE);
		break;
	
	    case DT_BLK:
	    case DT_CHR:
		printf("%s", YELLOW);
		break;
	
	    case DT_REG:
	    default:
	    
		/* Construct full path. */
		snprintf(tmp, sizeof(tmp),
			 "%s/%s", path, dent->d_name);
		
		/* Is the file executable? */
		if (stat(tmp, &st) != -1 && st.st_mode & 0100)
		{
		    printf("%s", GREEN);
		}
		else
		    printf("%s", WHITE);
	}
	printf("%s ", dent->d_name);
    }
    printf("\r\n");

    /* Close it. */
    closedir(d);
    
    /* Success. */
    return EXIT_SUCCESS;
}
