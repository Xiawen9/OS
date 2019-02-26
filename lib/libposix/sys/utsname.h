#ifndef __LIBPOSIX_UTSNAME_H
#define __LIBPOSIX_UTSNAME_H
#ifndef __ASSEMBLER__

#include <Macros.h>

/**
 * @defgroup libposix libposix (POSIX.1-2008)
 * @{
 */

/** Size of each buffer in the utsname structure fields. */
#define UTSBUF 128

/**
 * System name structure.
 */
struct utsname
{
    /** Name of this implementation of the operating system. */
    char sysname[UTSBUF];
    
    /**
     * Name of this node within the communications 
     * network to which this node is attached, if any.
     */
    char nodename[UTSBUF];

    /** Current release level of this implementation. */
    char release[UTSBUF];
    
    /** Current version level of this release. */
    char version[UTSBUF];
    
    /** Name of the hardware type on which the system is running. */  
    char machine[UTSBUF];
};

/**
 * Get the name of the current system
 * @param name Used to store information identifying the current system
 * @return Upon successful completion, a non-negative value shall be returned.
 *         Otherwise, -1 shall be returned and errno set to indicate the error.
 */
extern C int uname(struct utsname *name);

/**
 * @}
 */

#endif /* __ASSEMBLER__ */
#endif /* __LIBPOSIX_UTSNAME_H */
