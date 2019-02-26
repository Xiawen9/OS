#ifndef __LIBPOSIX_MATH_H
#define __LIBPOSIX_MATH_H

#include <Macros.h>

/**
 * @defgroup libposix libposix (POSIX.1-2008)
 * @{
 */

/**
 * Compute the absolute value of a number.
 *
 * The absolute value of a number turns it to positive
 * in case it is negative. Basically it just removes the sign (-) from a number.
 * For example, -3 returns 3, and 8 returns 8.
 *
 * @param number The number to make absolute.
 * @return Absolute value of the given number.
 */
extern C int abs(int number);

/**
 * Compute the square root of a number.
 *
 * @param number The number to use for square root.
 * @return Square root of the given number.
 */
extern C u32 sqrt(u32 number);

/**
 * @}
 */

#endif /* __LIBPOSIX_MATH_H */
