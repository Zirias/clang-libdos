unsigned short dosversion(void)
{
    unsigned short v1, v2;
    __asm__ (
	    "mov    $0x30, %%ah	    \n\t"
	    "int    $0x21	    \n\t"
	    : "=a" (v1)
	    :
	    : "bx", "cx"
	    );
    if (!(v1 & 0xff)) v1 = 0x0001;
    v2 = v1 >> 8 & 0xff;
    v1 = v1 << 8 | v2;
    return v1;
}

