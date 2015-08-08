all: lib/libdos.a

include mk/doslib.mk

libdos_TARGET:= libdos.a
libdos_TGTDIR:= lib
libdos_SRCDIR:= src
libdos_OBJDIR:= obj
libdos_ASMDIR:= asm
libdos_MODULES:= doscrt0 errno conio rtctimer \
	time/time_completetm time/time_getrtctm time/time_mktime \
	time/time_readrtc time/time_time \
	stdlib/stdlib_malloc stdlib/stdlib_rand \
	string/string_mem string/string_strerror string/string_strtok \
	string/string_strcpy string/string_strlen \
	stdio/stdio_core stdio/stdio_printf \
	curses/curses_core curses/curses_win curses/curses_bkgd \
	curses/curses_addch curses/curses_addstr curses/curses_erase \
	curses/curses_printw curses/curses_border

T:= libdos
$(eval $(DOSLIBRULES))

clean:
	rm -f $(CLEAN)
	rm -fr asm
	rm -fr obj

distclean: clean
	rm -f lib/libdos.a

.PHONY: all clean distclean

