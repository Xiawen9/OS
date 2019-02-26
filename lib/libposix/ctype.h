#ifndef __LIBC_CTYPE_H
#define __LIBC_CTYPE_H

#include <Character.h>

/** 
 * @defgroup libc libc (ISO C99)
 * @{ 
 */

/**
 * Test for a decimal digit.
 * @param c Input character.
 */
#define isdigit(c) Character::isDigit(c)

/**
 * Test for a lowercase letter.
 * @param c Input character.
 */
#define islower(c) Character::isLower(c)

/**
 * Test for an uppercase letter.
 * @param c Input character.
 */
#define isupper(c) Character::isUpper(c)

/**
 * Test for an alphabetic character.
 * @param c Input character.
 */
#define isalpha(c) Character::isAlpha(c)

/**
 * Test for an alphanumeric character.
 * @param c Input character.
 */
#define isalnum(c) Character::isAlnum(c)

/**
 * Test for a blank character.
 * @param c Input character.
 */
#define isblank(c) Character::isBlank(c)

/**
 * Test for a white-space character.
 * @param c Input character.
 */
#define isspace(c) Character::isSpace(c)

/**
 * Converts the letter c to lowercase.
 * @param c The letter to convert.
 * @return The converted letter, or c if conversion was not possible.
 */
#define tolower(c) Character::lower(c)

/**
 * Converts the letter c to uppercase.
 * @param c The letter to convert.
 * @return The converted letter, or c if conversion was not possible.
 */
#define toupper(c) Character::upper(c)

/**
 * @}
 */

#endif /* __LIBC_CTYPE_H */
