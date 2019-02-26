#ifndef __TYPES_H
#define __TYPES_H

#ifndef __ASSEMBLER__

<<<<<<< HEAD
/** 
 * @defgroup types types
 * @{ 
 */

/**
 * Restrict bit operations.
 */
#if 0
#define BITWISE \
    __attribute__((bitwise))
=======
/**
 * @defgroup types types
 * @{
 */

/**
 * Restrict bit operations. 
 * Ensure that variables are in the same bitwise manner.
 */
#if 0
#define BITWISE __attribute__((bitwise))
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
#else
#define BITWISE
#endif

/**
 * @name Unsigned integers.
 * @{
 */

/** Unsigned integer number. */
typedef unsigned int uint;

/** Unsigned long number. */
typedef unsigned long ulong;

/** Unsigned 64-bit number. */
typedef unsigned long long u64;

/** Unsigned 32-bit number. */
typedef unsigned int u32;

/** Unsigned 16-bit number. */
typedef unsigned short u16;

/** Unsigned 8-bit number. */
typedef unsigned char u8;

/**
 * @}
 */
<<<<<<< HEAD
 
=======

>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
/**
 * @name Signed integers.
 * @{
 */

/** Signed integer number. */
typedef signed int sint;

/** Signed long number. */
typedef signed long slong;

/** Signed 64-bit number. */
typedef signed long long s64;

/** Signed 32-bit number. */
typedef signed int s32;

/** Signed 16-bit number. */
typedef signed short int s16;

/** Signed 8-bit number. */
typedef signed char s8;

/**
 * @}
 */

/**
 * @name Bitwise checked integers.
 * @{
 */

/** Unsigned 64-bit little endian number. */
typedef u64 BITWISE le64;

/** Unsigned 64-bit big endian number. */
typedef u64 BITWISE be64;

/** Unsigned 32-bit little endian number. */
typedef u32 BITWISE le32;

/** Unsigned 32-bit big endian number. */
typedef u32 BITWISE be32;

/** Unsigned 16-bit little endian number. */
typedef u16 BITWISE le16;

/** Unsigned 16-bit big endian number. */
typedef u16 BITWISE be16;

/** Unsigned 8-bit little endian number. */
<<<<<<< HEAD
typedef u8  BITWISE le8;

/** Unsigned 8-bit big endian number. */
typedef u8  BITWISE be8;
=======
typedef u8 BITWISE le8;

/** Unsigned 8-bit big endian number. */
typedef u8 BITWISE be8;
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03

/**
 * @}
 */

/** Any sane size indicator cannot go negative. */
<<<<<<< HEAD
typedef unsigned int Size;

/** A memory address. */
typedef unsigned long Address;

/** User Identity. */
typedef unsigned short UserID;

/** Group Identity. */
typedef unsigned short GroupID;
=======
typedef uint Size;

/** A memory address. */
typedef ulong Address;

/** User Identity. */
typedef u16 UserID;

/** Group Identity. */
typedef u16 GroupID;
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03

/** Process Identification Number. */
typedef u16 ProcessID;

<<<<<<< HEAD
/**                                                                                   
 * Describes a device ID number.                                                      
 */                                                                                   
typedef struct DeviceID                                                               
{                                                                                     
    /** Major device ID number is a PID. */                                           
    ProcessID major;

    /** Device specific minor ID number. */
    u16 minor;
=======
/**
 * Describes a device ID number.
 */
typedef struct DeviceID
{
	/** Major device ID number is a PID. */
	ProcessID major;
	
	/** Device specific minor ID number. */
	u16 minor;
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
}
DeviceID;

/**
 * Error code defined in Error.h
 * @see Error.h
 */
typedef slong Error;

#ifdef __cplusplus
<<<<<<< HEAD

namespace Number
{
    /**
     * Numeral system base type.
     */
    typedef enum Base
    {
        Dec, /** Decimal: 0-10 */
        Hex, /** Hexadecimal: 0x0-0xf */
    }
    Base;
=======
 namespace Number
{
	/**
	 * Numeral system base type.
	 */
	typedef enum Base
	{
		Dec, /** Decimal: 0-10 */
		Hex, /** Hexadecimal: 0x0-0xf */
	}
	Base;
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
};

#endif /* __cplusplus */

/**
 * @}
 */

<<<<<<< HEAD
#endif /* __ASSEMBLER__ */
#endif /* __TYPES_H */
=======
#endif /** __ASSEMBLER__ */
#endif /** __TYPES_H */

>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
