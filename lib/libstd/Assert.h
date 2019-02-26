#ifndef __ASSERT_H
#define __ASSERT_H

#if defined(__ASSERT__) && !defined(__HOST__)

#include "Macros.h"
#include "Types.h"

#ifdef __SERVER__
#include <LogMessage.h>
#include <stdlib.h>
#endif /* __SERVER__ */

extern C void __assertFailure(const char *fmt, ...);
extern C int __assertRead(Address addr);
extern C int __assertWrite(Address addr);

#ifdef __SERVER__
#define raiseFailure(fmt, ...) \
    log(fmt, ##__VA_ARGS__); \
    exit(1);
#else
#define raiseFailure(fmt, ...) \
    __assertFailure(fmt, ##__VA_ARGS__);
#endif

#define assert(exp) \
    if (!(exp)) \
    { \
	raiseFailure("[%s:%d]: *** Assertion `%s' failed ***\n", \
		       __FILE__, __LINE__, #exp); \
    }

#define assertRead(addr) \
    assert(__assertRead((Address)addr))

#define assertWrite(addr) \
    assert(__assertWrite((Address)addr))

#else

/**
 * @brief Dummy preprocessor macros
 * @{
 */

#define assert(exp)
#define assertRead(addr)
#define assertWrite(addr)

#endif /* defined(__ASSERT__) && !defined(__HOST__) */
#endif /* __ASSERT_H */
