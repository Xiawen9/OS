#include "IntelConstant.h"
#include "IntelBoot.h" 

/** Initial stack size */
#define STACK_SIZE PAGESIZE

.global multibootEntry, multibootHeader

.section ".boot"

/*
 * Multiboot header, 32-bit aligned.
 */
.align 4

multibootHeader:
        .long  (MULTIBOOT_HEADER_MAGIC)
        .long  (MULTIBOOT_HEADER_FLAGS)
        .long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
        .long  (multibootHeader)

.section ".text"
.code32

/**
 * Entry point.
 */
multibootEntry:

    /* Disable interrupts. */
    cli

    /* Check multiboot magic */
    cmpl $MULTIBOOT_BOOTLOADER_MAGIC, %eax
    jnz useCoreInfo

    /* Setup temporary boot stack. */
    movl $(stack + STACK_SIZE), %esp
    movl %esp, %ebp

    /* Copy multiboot info to CoreInfo. */
    push %ebx
    call multibootToCoreInfo

    /* Jump to bootEntry32 */
    movl $coreInfo, %eax
    jmp bootEntry32

useCoreInfo:

    /* We started using a CoreInfo (AP core) */
    movl %eax, %ebx
    addl $12, %ebx
    movl (%ebx), %ebx

    /* Jump to bootEntry32 for this core */
    movl $bootEntry32, %ecx
    addl %ebx, %ecx
    jmp *%ecx

/**
 * Stop execution immediately.
 */
halt:
    cli
    hlt
    jmp halt

.section ".data"
.align PAGESIZE

stack: .fill STACK_SIZE, 1, 0
