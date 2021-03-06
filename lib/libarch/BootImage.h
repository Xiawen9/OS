#ifndef __LIBARCH_BOOTIMAGE_H
#define __LIBARCH_BOOTIMAGE_H

/** First magic byte. */
#define BOOTIMAGE_MAGIC0        ('F') + ('r' << 8) + ('e' << 16) + ('e' << 24)

/** Second magic byte. */
#define BOOTIMAGE_MAGIC1        ('N') + ('O' << 8) + ('S' << 16) + (0x1 << 24)

/** Version of the boot image layout. */
#define BOOTIMAGE_REVISION      2

/** Maximum length of BootSymbol names. */
#define BOOTIMAGE_NAMELEN       32

/**
 * BootImage contains executable programs to be loaded at system bootup.
 */
typedef struct BootImage
{
    /** Magic numbers to detect a valid boot image. */
    u32 magic[2];
    
    /** Version of the boot image layout. */
    u8  layoutRevision;
    
    /** Checksum used to verify integrity. */
    // TODO
    
    /** Offset of the symbol table. */
    u32 symbolTableOffset;
    
    /** Number of entries in the symbols table. */
    u16 symbolTableCount;
    
    /** Offset of the segments table. */
    u32 segmentsTableOffset;
    
    /** Number of entries in the segments table. */
    u16 segmentsTableCount;
}
BootImage;

/**
 * Boot symbol types.
 */
typedef enum BootSymbolType
{
    BootProgram    = 0,    /**< Executable program */
    BootFilesystem = 1,    /**< Embedded filesystem */
    BootData       = 2     /**< Binary data */
}
BootSymbolType;

/**
 * Program embedded in the BootImage.
 */
typedef struct BootSymbol
{
    /** Name of the boot symbol. */
    char name[BOOTIMAGE_NAMELEN];

    /** Type of boot symbol. */
    BootSymbolType type;

    /** Program entry point (only valid for BootProgram symbols). */
    u32 entry;
    
    /** Offset in the segments table. */
    u32 segmentsOffset;
    
    /** Number of contiguous entries in the segment table. */
    u16 segmentsCount;

    /** Total size of the BootSymbol segments */
    u32 segmentsTotalSize;
}
BootSymbol;

/**
 * Memory segment.
 */
typedef struct BootSegment
{
    /** Virtual memory address to load the segment. */
    u32 virtualAddress;
    
    /** Total size of the segment. */
    u32 size;
    
    /** Offset in the boot image of the segment contents. */
    u32 offset;
}
BootSegment;

#endif /* __LIBARCH_BOOTIMAGE_H */
