#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int readint(struct dirent *bus, struct dirent *slot,
	    struct dirent *func, const char *file)
{
    char str[256];
    int fd;
    
    /* Construct target path. */
    snprintf(str, sizeof(str), "/dev/pci/%s/%s/%s/%s",
	     bus->d_name, slot->d_name, func->d_name, file);
    
    /* Open the target file. */
    if ((fd = open(str, O_RDONLY)) < 0)
    {
	syslog(LOG_ERR, "failed to open() `%s': %s",
	       str, strerror(errno));
	exit(EXIT_FAILURE);
    }
    /* Read out the number as a string. */
    if (read(fd, str, sizeof(str)) <= 0)
    {
	syslog(LOG_ERR, "failed to read() `%s': %s",
	       str, strerror(errno));
	exit(EXIT_FAILURE);
    }
    close(fd);
    
    /* Convert string to binary number. */
    return strtol(str, ZERO, 0);
}

int main(int argc, char **argv)
{
    DIR *busDir, *slotDir, *funcDir;
    struct dirent *bus, *slot, *func;
    struct stat st;
    char path[256];
    const char *args[5];
    int vendor, device, revision, status, pid;

    /* Open logs. */
    openlog("PCI", LOG_PID, LOG_USER);

    /* Open the PCI filesystem. */    
    if (!(busDir = opendir("/dev/pci")))
    {
	syslog(LOG_ERR, "failed to opendir() `%s': %s",
			"/dev/pci", strerror(errno));
	return EXIT_FAILURE;
    }
    /*
     * Loop PCI bus(ses).
     */
    while ((bus = readdir(busDir)))
    {
	if (bus->d_name[0] == '.')
	{
	    continue;
	}
	snprintf(path, sizeof(path), "/dev/pci/%s",
		 bus->d_name);
    
	/* Open PCI slot directory. */
        if (!(slotDir = opendir(path)))
	{
	    syslog(LOG_ERR, "failed to opendir() `%s': %s",
			     path, strerror(errno));
	    return EXIT_FAILURE;
	}

	/*
	 * Loop PCI slot(s).
	 */
	 while ((slot = readdir(slotDir)))
	 {
	    if (slot->d_name[0] == '.')
	    {
		continue;
	    }
	    snprintf(path, sizeof(path), "/dev/pci/%s/%s",
		     bus->d_name, slot->d_name);
	
	    /* Open PCI function directory. */
	    if (!(funcDir = opendir(path)))
	    {
		syslog(LOG_ERR, "failed to opendir() `%s': %s\r\n",
				 path, strerror(errno));
		return EXIT_FAILURE;
	    }
	
	    /*
	     * Loop PCI function(s).
	     */
	    while ((func = readdir(funcDir)))
	    {
		if (func->d_name[0] == '.')
		{
		    continue;
		}
		/* Read out properties. */
		vendor   = readint(bus, slot, func, "vendor");
		device   = readint(bus, slot, func, "device");
		revision = readint(bus, slot, func, "revision");
		
		/* Log the device. */
                syslog(LOG_INFO, "[%s:%s:%s] %x:%x (rev %d)",
                       bus->d_name, slot->d_name, func->d_name,
		       vendor, device, revision);

		/* Construct path to a device driver server. */
		snprintf(path, sizeof(path), "/etc/pci/%x:%x",
			 vendor, device);
		
		/* Find device server, if any. */
		if (stat(path, &st) == 0)
		{
		    /* Setup argument list. */
		    args[0] = path;
		    args[1] = bus->d_name;
		    args[2] = slot->d_name;
		    args[3] = func->d_name;
		    args[4] = ZERO;
		
		    /* Execute it! */	
		    pid = forkexec(path, args);
		    waitpid(pid, &status, 0);
		}
		
	    }
	    closedir(funcDir);
	 }
	 closedir(slotDir);
    }
    closedir(busDir);
    return EXIT_SUCCESS;
}
