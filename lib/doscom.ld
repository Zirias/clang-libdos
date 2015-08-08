OUTPUT_FORMAT(binary)
ENTRY(__com__start)
SECTIONS
{
    . = 0x0100;
    .text :
    {
	*doscrt0.o(.comstartup);
	*(.text .text.*);
    }
    .data :
    {
	*(.data .data.*);
	*(.rodata .rodata.*);
	*(COMMON);
	*(.bss .bss.*);
    }
    /DISCARD/ :
    {
	*(.note*);
	*(.comment*);
    }
    _heap = ALIGN(4);
}

