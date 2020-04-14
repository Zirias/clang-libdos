# base flags needed for building .COM files with clang-libdos

CFLAGS+= -std=c99 -Os -nostdlib -m16 -march=i386 -ffreestanding -fno-builtin -fno-pic -fno-pie -fno-strict-aliasing -fomit-frame-pointer -fno-stack-protector -fno-inline-functions -mno-mmx -mno-sse
INCLUDES+= -nostdinc -I$(LIBDOSPATH)/include
LDFLAGS+= -Wl,--omagic,-melf_i386,--script=$(LIBDOSPATH)/lib/doscom.ld \
	  -L$(LIBDOSPATH)/lib -fuse-ld=bfd
LIBRARIES+= -ldos

