#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    char host[128];

    /* Fetch hostname. */
    gethostname(host, sizeof(host));
    
    /* Output our hostname. */
    printf("%s\r\n", host);
    
    /* Done. */
    return EXIT_SUCCESS;
}
