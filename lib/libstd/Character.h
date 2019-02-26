#ifndef __LIBSTD_CHARACTER_H
#define __LIBSTD_CHARACTER_H

namespace Character
{
    /**
     * Test for a decimal digit.
     * @param c Input character.
     */
    inline bool isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    /**
     * Test for a wildcard character.
     *
     * @param c Input character.
     * @return True if wildcard, false otherwise.
     */
    inline bool isWildcard(char c)
    {
        return c == '*';
    }

    /**
     * Test for a lowercase letter.
     *
     * @param c Input character.
     */
    inline bool isLower(char c)
    {
        return (c) >= 'a' && (c) <= 'z';
    }

    /**
     * Test for an uppercase letter.
     *
     * @param c Input character.
     */
    inline bool isUpper(char c)
    {
        return (c) >= 'A' && (c) <= 'Z';
    }

    /**
     * Test for an alphabetic character.
     * @param c Input character.
     */
    inline bool isAlpha(char c)
    {
        return isUpper(c) || isLower(c);
    }

    /**
     * Test for an alphanumeric character.
     *
     * @param c Input character.
     */
    inline bool isAlnum(char c)
    {
        return isAlpha(c) || isDigit(c);
    }

    /**
     * Test for a blank character.
     *
     * @param c Input character.
     */
    inline bool isBlank(char c)
    {
        return (c) == ' ' || (c) == '\t';
    }

    /**
     * Test for a white-space character.
     *
     * @param c Input character.
     */
    inline bool isWhitespace(char c)
    {
        return (c) == '\v' || (c) == '\f' ||
               (c) == '\r' || (c) == '\n' || isBlank(c);
    }

    /**
     * Converts the letter c to lowercase.
     *
     * @param c The letter to convert.
     * @return The converted letter, or c if conversion was not possible.
     */
    inline char lower(char c)
    {
        return (c >= 'A' && c <= 'Z') ? (c + 32) : (c);
    }

    /**
     * Converts the letter c to uppercase.
     *
     * @param c The letter to convert.
     * @return The converted letter, or c if conversion was not possible.
     */
    inline char upper(char c)
    {
        return (c >= 'a' && c <= 'z') ? (c - 32) : (c);
    }
};

#endif /* __LIBSTD_CHARACTER_H */
