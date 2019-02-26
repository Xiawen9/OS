#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/wait.h>

void banner()
{
    struct utsname uts;

    if (uname(&uts) != -1)
    {
        printf("\r\n%s %s\r\n\r\nlogin: ",
            uts.sysname,
            uts.release
        );
    }
}

char * getuser()
{
    static char line[1024];
    Size total = 0;
    
    /* Read a line. */
    while (total < sizeof(line))
    {
        /* Read a character. */
        read(0, line + total, 1);

        /* Process character. */
        switch (line[total])
        {
            case '\r':
            case '\n':
                printf("\r\n");
                line[total] = ZERO;
                return line;

            case '\b':
                if (total > 0)
                {
                    total--;
                    printf("\b \b");
                }
                break;
        
            default:
                printf("%c", line[total]);
                total++;
                break;
        }
    }
    line[total] = ZERO;
    return line;
}

int main(int argc, char **argv)
{
    char *user;
    const char *sh_argv[] = { "/bin/sh", 0 };

    pid_t pid;
    int status;

    // Check arguments
    if (argc < 3)
    {
        printf("usage: %s INPUT OUTPUT\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Wait until the I/O files are available (busy loop)
    while (true)
    {
        // Re-open standard I/O
        close(0);
        close(1);
        close(2);

        // Stdin
        if (open(argv[1], O_RDONLY) == -1)
            continue;

        // Stdout
        if (open(argv[2], O_RDWR) == -1)
            continue;

        // Stderr
        if (open(argv[2], O_RDWR) == -1)
            continue;

        // Done
        break;
    }

    // Loop forever with a login prompt
    while (true)
    {
        banner();
        user = getuser();

        if (strlen(user) > 0)
        {
            // Start the shell
            if ((pid = forkexec("/bin/sh", sh_argv)) != (pid_t) -1)
            {
                waitpid(pid, &status, 0);
            }
            else
            {
                printf("forkexec '%s' failed: %s\r\n", argv[0],
                        strerror(errno));
            }
        }
    }
    return EXIT_SUCCESS;
}
