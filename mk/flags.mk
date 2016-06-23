# base flags needed for building .COM files with clang-libdos

CFLAGS+= -std=c99 -Os -nostdlib -m16 -march=i386 -ffreestanding
ASMFLAGS+= --32 -march=i586
INCLUDES+= -nostdinc -I$(LIBDOSPATH)/include
LDFLAGS+= -Wl,--omagic,--script=$(LIBDOSPATH)/lib/doscom.ld \
	  -L$(LIBDOSPATH)/lib -fuse-ld=bfd
LIBRARIES+= -ldos

