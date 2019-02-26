#ifndef __LIBARCH_INTEL_MP_H
#define __LIBARCH_INTEL_MP_H

/** Physical memory address for the CoreInfo structure. */
#define MPINFOADDR 0x10000

#ifndef __ASSEMBLER__

#include <Types.h>
#include <List.h>
#include <BitOperations.h>
#include <IntController.h>
#include <CoreInfo.h>
#include <CoreManager.h>
#include "IntelIO.h"
#include "IntelAPIC.h"


/** Forward declarations */
class MemoryContext;
class IntelPIT;

/**
 * Intel Multi-Processor Specification.
 */
class IntelMP : public CoreManager
{
  private:

    /** Multiprocessor Floating Structure Signature. */
    static const uint MPFloatSignature = 0x5f504d5f;

    /** Multiprocessor Configuration Type ID for processors. */
    static const uint MPEntryProc = 0;

    /** Physical memory address at which cores start (bootEntry16). */
    static const Address MPEntryAddr = 0xf000;

    /** Physical memory address for the CoreInfo structure. */
    static const Address MPInfoAddr = MPINFOADDR;

    /** BIOS memory area to search for MP tables */
    static const Address MPAreaAddr = 0x1000;

    /** BIOS memory area size to search for MP tables */
    static const Size MPAreaSize = 0x100000-0x1000;

    /**
     * Multiprocessor Floating Structure.
     */
    typedef struct MPFloat
    {
        unsigned long signature;
        unsigned long configAddr;
        unsigned char length;
        unsigned char revision;
        unsigned char checksum;
        unsigned char feature1;
        unsigned long feature2;
    }
    MPFloat;

    /**
     * Multiprocessor Configuration Structure.
     */
    typedef struct MPConfig
    {
        char signature[4];
        unsigned short length;
        unsigned char revision;
        unsigned char checksum;
        char oemId[8];
        char productId[12];
        unsigned long oemAddr;
        unsigned short oemLength;
        unsigned short count;
        unsigned long apicAddr;
        unsigned long reserved;
    }
    MPConfig;

    /**
     * Multiprocessor Configuration Entry.
     */
    typedef struct MPEntry
    {
        unsigned char type;
        unsigned char apicId;
        unsigned char apicRevision;
        unsigned char cpuFlags;
        u32 signature;
        u32 features;
        u32 reserved[2];
    }
    MPEntry;

  public:

    /**
     * Constructor
     */
    IntelMP();

    /**
     * Discover processors.
     *
     * @return Result code.
     */
    virtual Result discover();

    /**
     * Boot a processor.
     *
     * @param info CoreInfo object pointer.
     * @return Result code.
     */
    virtual Result boot(CoreInfo *info);

  private:

    /**
     * Parse Multiprocessor Config entry.
     *
     * @return MPEntry object pointer of the next entry.
     */
    MPEntry * parseEntry(MPEntry *entry);

    /**
     * Scan memory for a Multiprocessor Config structure.
     *
     * @return MPConfig object pointer on success or ZERO on failure.
     */
    MPConfig * scanMemory(Address addr);

    /** I/O instance for BIOS memory */
    IntelIO m_bios;

    /** I/O instance for the last 1MB of physical memory */
    IntelIO m_lastMemory;

    /** APIC instance */
    IntelAPIC m_apic;
};

#endif /* __ASSEMBLER__ */
#endif /* __LIBARCH_INTEL_MP_H */
