OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x0100;
    .text :
    {
	*doscrt0.o(.comstartup);
	*(.text*);
    }
    .data :
    {
	*(.data*);
	*(.rodata*);
	*(COMMON);
	*(.bss*);
    }
    /DISCARD/ :
    {
	*(.note*);
	*(.comment*);
    }
    _heap = ALIGN(4);
}

