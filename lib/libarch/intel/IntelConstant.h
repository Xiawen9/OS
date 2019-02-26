#ifndef __LIBARCH_INTEL_CONSTANT_H
#define __LIBARCH_INTEL_CONSTANT_H

/**
 * Intel CPU Constants
 * @{
 */

/** Intel is little endian. */
#define CPU_LITTLE_ENDIAN 1

/** Protected Mode. */
#define CR0_PE          0x00000001

/** Paged Mode. */
#define CR0_PG          0x80000000

/** Timestamp Counter Disable. */
#define CR4_TSD         0x00000004
#define CR4_PSE         (1 << 4)

/** Kernel Code Segment. */
#define KERNEL_CS       1 
#define KERNEL_CS_SEL   0x8 

/** System Data Segment. */
#define KERNEL_DS       2 
#define KERNEL_DS_SEL   0x10 
    
/** User Code Segment. */
#define USER_CS         3 
#define USER_CS_SEL     (0x18 | 3) 
        
/** User Data Segment. */
#define USER_DS         4 
#define USER_DS_SEL     (0x20 | 3) 

/** Kernel Task State Segment. */
#define KERNEL_TSS      5 
#define KERNEL_TSS_SEL  0x28 

/**
 * @}
 */

/**
 * Intel Memory Constants.
 * @{
 */

/** Page entry bit shift. */
#define PAGESHIFT       12

/** Page table bit shift. */
#define DIRSHIFT        22

/** Intel uses 4K pages. */
#define PAGESIZE        4096

/** Number of entries in the page directory. */
#define PAGEDIR_MAX     1024

/** Number of entries in a page table. */
#define PAGETAB_MAX     1024

/** Mask to find the page. */
#define PAGEMASK        0xfffff000 

/** Memory address alignment. */
#define MEMALIGN        4

/**
 * @}
 */

#endif /* __LIBARCH_INTEL_CONSTANT_H */
