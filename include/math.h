#ifndef LIBDOS_MATH_H
#define LIBDOS_MATH_H

static inline double sqrt(double x)
{
    __asm__ (
	    "fldl   %0	    \n\t" \
	    "fsqrt	    \n\t" \
	    "fstpl   %0	    \n\t" \
	    : "=m" ((x))
	    : "m" ((x))
	    );
    return x;
}

#endif
