all: example.com

LIBDOSPATH:= ..

include $(LIBDOSPATH)/mk/doscom.mk

example_TARGET:= example.com
example_SRCDIR:= .
example_MODULES:= main

T:= example
$(eval $(DOSCOMRULES))

clean:
	rm -f $(CLEAN)

distclean: clean
	rm -f example.com

.PHONY: all clean distclean

