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
	_data = .;
	*(.data);
	_rodata = .;
	*(.rodata);
	_common = .;
	*(COMMON);
	_bss = .;
	*(.bss);
	FILL(0x00000000);
    }
    _heap = ALIGN(4);
}

