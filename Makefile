BINARY:= test.com
SOURCES:= src/main.c
LIBDOS:= src/libdos/core.c src/libdos/stdlib.c src/libdos/string.c \
	src/libdos/stdio.c src/libdos/time.c src/libdos/conio.c
LDSCRIPT:= com.ld

CFLAGS:= -std=c99 -Os -nostdlib -m16 -march=i386 -ffreestanding
LDFLAGS:= -Wl,--nmagic,--script=$(LDSCRIPT)

ALLSRC:= $(LIBDOS) $(SOURCES)

all: $(BINARY)

$(BINARY): $(ALLSRC) | $(LDSCRIPT)
	clang -o$@ $(CFLAGS) $(LDFLAGS) $^

.PHONY: all $(BINARY)
