#ifndef LIBDOS_STDDEF_H
#define LIBDOS_STDDEF_H

typedef int const FILE;
typedef unsigned short size_t;

enum
{
    EINVAL = 1,
    ENOSYS,
    ENODEV,
    ECANCELED,
    EBUSY,
    ENOMEM
};

#endif
