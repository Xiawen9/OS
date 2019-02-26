ENTRY(_entry)
TARGET("elf32-littlearm")
OUTPUT_FORMAT("elf32-littlearm")

SECTIONS
{
    . = 0x80000000;

    .text :
    {
	*(.entry)
	*(.text)
	*(*.text)
	*(.gnu.linkonce.*)
	*(.data)
	*(.rodata)
	*(.rodata.*)
	*(.eh_frame)
        *(.note.gnu.build-id)

	. = ALIGN(4);
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
        KEEP (*(.dtors))
        KEEP (*(.fini_array.*))
        KEEP (*(.fini_array))
        LONG(0)
        DTOR_END = .;

        isKernel = .;
        LONG(0);
	. += 4;

	
	initStart = .;
	KEEP (*(SORT(.init*)))
	KEEP (*(.init*))
	initEnd   = .;

        . = ALIGN(4096);
        __bss_start = .;
        *(.bss)
        . = ALIGN(4096); /* align to page size */
        __bss_end = .;
    }
}
