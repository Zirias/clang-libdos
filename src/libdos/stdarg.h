#ifndef LIBDOS_STDARG_H
#define LIBDOS_STDARG_H

typedef unsigned char *va_list;
#define va_start(list, param) (list = (((va_list)&param) + sizeof(param)))
#define va_arg(list, mode) ((mode *)(list = (char *)list + sizeof(mode)))[-1]

#endif
