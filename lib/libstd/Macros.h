#ifndef __MACROS_H
#define __MACROS_H

#include "Types.h"

<<<<<<< HEAD
#define TRUE		1
#define FALSE		0

=======
/** Binary 1 means true. */
#define TRUE		1

/** Binary zero means false. */
#define FALSE		0

/** NULL means zero. */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
#ifndef NULL
#define NULL		(void *)0
#endif

<<<<<<< HEAD
#define ZERO		0
#define QUOTE(x)  #x
#define IQUOTE(x) QUOTE(x)

#define KiloByte(v) ((v) * 1024)
#define MegaByte(v) ((v) * 1024 * 1024)
#define GigaByte(v) ((v) * 1024 * 1024 * 1024)

#define LONG_MIN -2147483647L
#define LONG_MAX  2147483647L
#define ULONG_MIN 0LU
#define ULONG_MAX 4294967295LU
#define INT_MIN -2147483647
#define INT_MAX  2147483647
#define UINT_MIN 0U
#define UINT_MAX 4294967295U

=======
/** Zero value. */
#define ZERO		0

/** Stringfies the given input. */
#define QUOTE(x) \
    #x

/** Indirect quoting. */
#define IQUOTE(x) \
    QUOTE(x)

/** Convert kilobytes to bytes */
#define KiloByte(v) ((v) * 1024)

/** Convert megabytes to bytes */
#define MegaByte(v) ((v) * 1024 * 1024)

/** Convert gigabytes to bytes */
#define GigaByte(v) ((v) * 1024 * 1024 * 1024)

// TODO: #warning Integer range depends on the architecture. Move to libarch.

/** Minimum value of an object of type long int. */
#define LONG_MIN -2147483647L

/** Maximum value of an object of type long int. */
#define LONG_MAX  2147483647L

#define ULONG_MIN 0LU

#define ULONG_MAX 4294967295LU

#define INT_MIN -2147483647

#define INT_MAX  2147483647

#define UINT_MIN 0U

#define UINT_MAX 4294967295U

/**
 * Calculate a division, and round to up any remaining.
 * @param number Input number.
 * @param divisor Divisor number.
 * @return Ceiled number.
 */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
#define CEIL(number,divisor) \
    ( (number) % (divisor) ?  \
     ((number) / (divisor)) + 1 : (number) / (divisor))

#ifdef __cplusplus

<<<<<<< HEAD
=======
/**
 * Absolute value of a double.
 */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
inline double doubleAbsolute(double number)
{
    return number < 0 ? -number : number;
}

<<<<<<< HEAD
=======
/**
 * Compare two doubles using a epsilon number as precision indicator.
 */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
inline bool doubleEquals(double a, double b, double epsilon)
{
    return doubleAbsolute(a - b) < epsilon;
}

#endif /* __cplusplus */

/** Calculates offsets in data structures. */
#define offsetof(TYPE, MEMBER) \
    ((Size) &((TYPE *)0)->MEMBER)

/** Used to define external C functions. */
#ifdef __cplusplus
#define C "C"
#define CPP
#else
#define C
#endif /* c_plusplus */

<<<<<<< HEAD
#define SECTION(s) \
    __attribute__((__section__(s)))


=======
/**
 * Can be used to link a symbol inside a specific section.
 * @param s Section name.
 */
#define SECTION(s) \
    __attribute__((__section__(s)))

/**
 * Declares an symbol to be forcibly "used".
 */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
#define USED \
    __attribute__((__used__))

/**
 * Ensures strict minimum memory requirements.
 * This option effectively disabled extra padding by the compiler.
 */
#define PACKED \
    __attribute__((__packed__))

/**
 * Aligns a symbol at the given boundary.
 * @param n Boundary to align.
 */
#define ALIGN(n) \
    __attribute__((aligned(n)))

#endif /* __MACROS_H */
