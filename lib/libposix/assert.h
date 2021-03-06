#ifndef __LIBC_ASSERT_H
#define __LIBC_ASSERT_H

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"

/**
 * @defgroup libc libc (ISO C99)
 * @{
 */

/**
 * @brief Insert program diagnostics.
 *
 * The assert() macro shall insert diagnostics into programs; it shall
 * expand to a void expression. When it is executed, if expression
 * (which shall have a scalar type) is false (that is, compares equal to 0),
 * assert() shall write information about the particular call that failed on
 * stderr and shall call abort().
 *
 * The information written about the call that failed shall include the text
 * of the argument, the name of the source file, the source file line number,
 * and the name of the enclosing function; the latter are, respectively, the
 * values of the preprocessing macros __FILE__ and __LINE__ and of the
 * identifier __func__.
 *
 * Forcing a definition of the name NDEBUG, either from the compiler command
 * line or with the preprocessor control statement #define NDEBUG ahead of
 * the #include <assert.h> statement, shall stop assertions from being
 * compiled into the program.
 *
 * @param exp Boolean expression.
 * @return The assert() macro shall not return a value.
 */
#ifdef NDEBUG
#define assert(ignore) ((void) 0)
#else
#define assert(exp) \
    if (!(exp)) \
    { \
        printf("[%s:%d]: *** Assertion `%s' failed ***\n", \
                __FILE__, __LINE__, #exp); \
	exit(1); \
    }
#endif

/**
 * @}
 */

#endif /* __LIBC_ASSERT_H */
