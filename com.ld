OUTPUT_FORMAT(binary)
SECTIONS
{
    . = 0x0100;
    .text :
    {
	*(.text);
    }
    .data :
    {
	*(.data);
	*(.rodata);
	*(COMMON);
	*(.bss);
    }
    _heap = ALIGN(4);
}

