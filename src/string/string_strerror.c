#include <string.h>

#include <errno.h>
#include <stdio.h>

char *strerror(int errnum)
{
    static char unknown[18];
    switch (errnum)
    {
	case EINVAL: return "Invalid argument";
	case ENOSYS: return "Function not implemented";
	case ENODEV: return "No such device";
	case ECANCELED: return "Operation canceled";
	case EBUSY: return "Device or resource busy";
	case ENOMEM: return "Not enough space";
    }
    errno = EINVAL;
    snprintf(unknown, 18, "Unknown error %03d", errnum);
    return unknown;
}

