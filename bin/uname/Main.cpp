#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/utsname.h>

int main(int argc, char **argv)
{
    struct utsname info;

    /* Retrieve version information. */
    if (uname(&info) < 0)
    {
	printf("%s: uname() failed: %s\r\n",
		argv[0], strerror(errno));
	return errno;
    }
    /* If no argument given, show the system name. */
    if (argc <= 1)
    {
	printf("%s", info.sysname);
    }
    /* Otherwise, interpret argument(s). */
    else
    {
	for (int i = 0; i < argc - 1; i++)
	{
	    /* System name. */
	    if (strcmp(argv[i + 1], "-s") == 0)
		printf("%s ", info.sysname);
	
	    /* Node name. */
	    else if (strcmp(argv[i + 1], "-n") == 0)
		printf("%s ", info.nodename);
	
	    /* Release. */
	    else if (strcmp(argv[i + 1], "-r") == 0)
		printf("%s ", info.release);
	
	    /* Version. */
	    else if (strcmp(argv[i + 1], "-v") == 0)
		printf("%s ", info.version);
	
	    /* Machine name. */
	    else if (strcmp(argv[i + 1], "-m") == 0)
		printf("%s ", info.machine);

	    /* Everything. */
	    else if (strcmp(argv[i + 1], "-a") == 0)
	        printf("%s %s %s %s %s ",
            		info.sysname,
        	        info.nodename,
        		info.release,
            		info.version,
            		info.machine);

	    /* Help message. */
	    else if (strcmp(argv[i + 1], "-h") == 0)
	    {
		printf( "usage: %s [OPTION]...\r\n"
			"Print system information.\r\n"
			"\r\n"
			"-h     Show this help message\r\n"
			"-a     Print all information in the following order:\r\n"
			"-s     Print the system name.\r\n"
			"-n     Print the network hostname.\r\n"
			"-r     Print the kernel release.\r\n"
			"-v     Print the kernel version.\r\n"
			"-m     Print the machine name.\r\n", argv[0]);
		return EXIT_SUCCESS;
	    }
	    /* Unknown argument. */
	    else
	    {
		printf("%s: invalid argument `%s'\r\n",
			argv[0], argv[i + 1]);
		return EXIT_FAILURE;
	    }
	}
    }
    /* Terminate with a newline. */
    printf("\r\n");
    
    /* Done. */
    return EXIT_SUCCESS;
}
