#ifndef __LIBPOSIX_LIBGEN_H
#define __LIBPOSIX_LIBGEN_H

#include <Macros.h>

/**                                                                                                                                                                                                     
 * @defgroup libposix libposix (POSIX.1-2008)
 * @{
 */ 

/**
 * @brief Return the last component of a pathname.
 *
 * The basename() function shall take the pathname
 * pointed to by path and return a pointer to the
 * final component of the pathname, deleting any
 * trailing '/' characters.
 *
 * @param path Filesystem path.
 * @return String pointer to the last component.
 */
extern C char * basename(char *path);

/**
 * @brief Return the directory portion of a pathname.
 * @return String pointer to the directory of pathname.
 */
extern C char * dirname(char *path);

/**
 * @}
 */

#endif /* __LIBPOSIX_LIBGEN_H */
