LIBDOSPATH?= .

include $(LIBDOSPATH)/mk/silent.mk
include $(LIBDOSPATH)/mk/config.mk
include $(LIBDOSPATH)/mk/flags.mk
include $(LIBDOSPATH)/mk/objs.mk

define DOSLIBRULES
$(OBJRULES)

$$($(T)_TGTDIR)/$$($(T)_TARGET): $$($(T)_OBJS) | $$($(T)_TGTDIR)
	$$(VAR)
	$$(VR)rm -f $$@
	$$(VR)ar rcs $$@ $$^

endef
