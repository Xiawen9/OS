ENTRY(multibootEntry)
TARGET("elf32-i386")
OUTPUT_FORMAT("elf32-i386")

phys = 0x00100000;
virt = 0x00100000;

SECTIONS
{
    . = 0x00100000;
    kernelStart = .;

    .text virt : AT(phys)
    {
        code = .;
        *(.boot)
        *(.text)
        *(*.text)
        *(.gnu.linkonce.*)
        *(.rodata)
        *(.rodata.*)
        *(.eh_frame)
        . = ALIGN(4096);
    }

    .data : AT (phys + (data - code))
    {
        data = .;
        *(.data)
        *(.note.gnu.build-id)

        CTOR_LIST = .;
        KEEP (*(SORT(.ctors.*)))
        KEEP (*(.ctors))
        KEEP (*(.preinit_array))
        KEEP (*(.init_array.*))
        KEEP (*(.init_array))
        LONG(0)
        CTOR_END = .;

        DTOR_LIST = .;
        KEEP (*(SORT(.dtors.*)))
        KEEP (*(.dtors))
        KEEP (*(.fini_array.*))
        KEEP (*(.fini_array))
        LONG(0)
        DTOR_END = .;
        . += 4;

        initStart = .;
        KEEP (*(SORT(.init*)))
        initEnd   = .;
        isKernel = .;
        LONG(1);
        . = ALIGN(4096);
    }

    .bss : AT(phys + (bss - code))
    {
        bss = .;
        *(.bss)
        *(.bss.*)
        *(COMMON)

        . += 4;
        kernelEnd = .;

        . = 0x00400000;
    }
}
