# clang-libdos

This is work in progress, but the parts finished are usable.

### What's this?

In short: A little collection trying to mimic the most basic parts of a C
standard library for *real mode* DOS programs (`.COM` files).

If you try creating a *real mode* DOS program, you either use some ages-old
compilers (or, compilers using ages-old syntax ... *K&R* that is), or you're
completely on your own, left with nothing but the BIOS and DOS *interrupt
routines*, accessible through inline assembly. This random collection of code
tries to fill the gap.

`LLVM/clang` (and, more recently, `GCC`) provide the `-m16` switch for
compiling to *real mode* code. It's a bit counter-intuitive, because this
still creates code making use of all the *long* instructions and 32bit
registers, so the code will not work on any processor that doesn't support the
whole *i386* instruction set. It just means it will run in the 16bit-"based"
*real mode*, so it's possible to create a DOS `.COM` executable with a little
linker magic. Read [this very interesting blog post by Christopher
Wellons](http://nullprogram.com/blog/2014/12/09/) for more details -- it's a
great read and it was written before the `-m16` switch was introduced, so
things were even more complicated.

### How does this relate to clang?

Well, `GCC` seems still a bit more *buggy* with `-m16` than `clang`. `clang`
already does a great job optimizing the code without breaking it for *real
mode*. Apart from that, there's one issue: *real mode* applications typically
use BIOS and DOS *interrupt routines*. Some BIOSes are buggy. There's at least
one routine (the one for scrolling the console, so something needed regularly)
I know of that clobbers the `ebp` (base pointer for the current stack frame)
register on buggy BIOSes. Declaring that in your inline assembly, `GCC` just
refuses to compile.[1] `clang` doesn't complain. As I don't know of any other
*modern* compilers targeting *real mode*, this project is now tied to `clang`.

## Features

 - basic heap management (`malloc()` and friends). `realloc()` is currently
   untested, `calloc()` is not (yet?) supported.

 - A non-standard `conio.h` interface aiming to provide an API around the most
   commonly used `int 10h` BIOS routines.

 - A non-standard `rtctimer.h` providing a waitable timer on top of BIOS RTC
   timer routines. Values are given in microseconds, but the typical precision
   available is 977 µs. This doesn't seem to work with every BIOS (works in
   DOSBox, *doesn't* work in VirtualBox), so maybe replace with some assembly
   implementation using the RTC directly later ...

 - very limited `libc` functionality, including the `*printf()` family [2],
   error handling through `errno.h`, *some* `string.h` functions, *some*
   `time.h` functions, a very simple PRNG for `rand()` and *fake* stdio
   streams just for `stdin`, `stdout` and `stderr`. See the source for
   details.

 - **very** limited `curses.h` emulation, which could be enough for very basic
   curses-based programs. Handling of WINDOWs and comparison of physical and
   virtual screen *are* implemented, but be warned that this consumes memory
   ... a precious thing in a `.COM` file limited to 64KB. So, if you don't
   need curses, just leave `curses.o` out when linking.

## Why?

Because we can. My goal right now is to implement enough *runtime foo* to get
my [cursedsnake game](https://github.com/Zirias/cursedsnake) to compile to a
working `.COM` file. Just for fun. **Update 2015-08-07**: This is finally
working. Have a look at the `libdos.mk` Makefile over there on how to use this
project in a real-world app/game.

## How to use?

See the Makefile in this repository. It has some options enabled to save space
like passing up to 3 arguments in registers and letting the linker eliminate
unused code and data. At the time being, the `clang` available in Debian
stable messes up at the assembler step with at least one instruction (`lea`)
when compiling for *real mode*. This would lead to strange 
*[heisenbugs](http://stackoverflow.com/questions/31865276/)* in the resulting
binary. So, for now, the Makefile lets `clang` only create optimized assembly
source, which is then passed to the GNU assembler.

**Important**: `core.o` **must** be the first object file on your linking
stage commandline. It contains the startup code and as `.COM` doesn't have any
headers, whatever comes first in the binary will be executed at startup.

If you don't need commandline arguments in your program (so, if your main
function is declared `int main(void)`), pass `-DNOARGV` while compiling to
save a few bytes in the startup code.

## Footnotes

 - [1] The `Linux` kernel uses `GCC` for its bootcode. They came up with a big
       wrapper done in assembly around BIOS *interrupt routines* saving and
       restoring **all** registers, obviously being fed up with BIOS bugs. Of
       course, that's a nice approach for boot code, but in your *real mode*
       DOS application, you probably don't want to do such a thing.

 - [2] In the current implementation, the only format specifiers allowed are
       `s`, `c`, `d`, `u`, `x` and `X`. Flags for padding (` ` and `0`) and
       field-widths are understood as well as length specifiers from `hh` to
       `l`. No advanced features of `printf()` are supported and there's
       barely any error-checking, so be careful with your format strings. For
       `s` and `c`, any flags and field-widths are currently ignored.

