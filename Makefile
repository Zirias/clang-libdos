BINARY:= test.com
SOURCES:= src/main.c
LIBDOS:= src/libdos/core.c src/libdos/stdlib.c src/libdos/string.c \
	src/libdos/stdio.c src/libdos/time.c src/libdos/conio.c \
	src/libdos/rtctimer.c src/libdos/curses.c
LDSCRIPT:= com.ld

CFLAGS:= -std=c99 -Oz -nostdlib -m16 -march=i386 -mregparm=3 \
    -ffreestanding -fdata-sections -ffunction-sections \
    -I./src/libdos -Wall -Wextra -pedantic
LDFLAGS:= -Wl,--omagic,--script=$(LDSCRIPT),--gc-sections

ALLSRC:= $(LIBDOS) $(SOURCES)

all: $(BINARY)

$(BINARY): $(ALLSRC:.c=.o) | $(LDSCRIPT)
	clang -o$@ $(CFLAGS) $(LDFLAGS) $^

%.o: %.c

%.o: %.s
	echo \\t.code16 | cat - $< | as --32 -march=i586 -o$@

%.s: %.c
	clang -S -o$@ $(CFLAGS) $<

clean:
	rm -f $(ALLSRC:.c=.o)
	rm -f $(ALLSRC:.c=.s)

.PHONY: all clean $(BINARY)
