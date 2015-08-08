LIBDOSPATH?= .

include $(LIBDOSPATH)/mk/silent.mk
include $(LIBDOSPATH)/mk/config.mk
include $(LIBDOSPATH)/mk/flags.mk
include $(LIBDOSPATH)/mk/objs.mk

define DOSCOMRULES
$(OBJRULES)

$$($(T)_TGTDIR)/$$($(T)_TARGET): $$($(T)_OBJS) | $$($(T)_TGTDIR)
	$$(VCCLD)
	$$(VR)$$(CC) -o$$@ $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_LDFLAGS) $$(LDFLAGS) $$($(T)_OBJS) \
		$$($(T)_LIBRARIES) $$(LIBRARIES)

$$($(T)_TGTDIR)/$$($(T)_TARGET): $$(LIBDOSPATH)/lib/libdos.a

$$(LIBDOSPATH)/lib/libdos.a:
	$$(MAKE) -C $$(LIBDOSPATH)

endef

