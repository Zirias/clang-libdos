define OBJRULES

$(T)_TGTDIR?= $$($(T)_SRCDIR)
$(T)_ASMDIR?= $$($(T)_SRCDIR)
$(T)_OBJDIR?= $$($(T)_SRCDIR)

$(T)_SOURCES:= $$(addprefix $$($(T)_SRCDIR)/, \
	$$(addsuffix .c,$$($(T)_MODULES)))
$(T)_OBJS:= $$(addprefix $$($(T)_OBJDIR)/, \
	$$(addsuffix .o,$$($(T)_MODULES)))

CLEAN+= $$($(T)_OBJS:.o=.d) $$($(T)_OBJS)

ifneq ($$(strip $$($(T)_TGTDIR)),$$(strip $$($(T)_SRCDIR)))
$$($(T)_TGTDIR):
	$$(VMD)
	$$(VR)mkdir -p $$(addprefix $$($(T)_TGTDIR)/, $$(dir $$($(T)_MODULES)))

endif
ifneq ($$(strip $$($(T)_OBJDIR)),$$(strip $$($(T)_SRCDIR)))
$$($(T)_OBJDIR):
	$$(VMD)
	$$(VR)mkdir -p $$(addprefix $$($(T)_OBJDIR)/, $$(dir $$($(T)_MODULES))) 

endif

%.o: %.c

$$($(T)_OBJDIR)/%.d: $$($(T)_SRCDIR)/%.c Makefile conf.mk | $$($(T)_OBJDIR)
	$$(VDEP)
	$$(VR)$$(CC) -MM -MT"$$@ $$(@:.d=.o)" -MF$$@ \
		$$($(T)_CFLAGS) $$(CFLAGS) $$($(T)_INCLUDES) $$(INCLUDES) $$<

ifneq ($$(MAKECMDGOALS),clean)
ifneq ($$(MAKECMDGOALS),distclean)
-include $$($(T)_OBJS:.o=.d)
endif
endif

$$($(T)_OBJDIR)/%.o: $$($(T)_SRCDIR)/%.c Makefile conf.mk | $$($(T)_OBJDIR)
	$$(VCC)
	$$(VR)$$(CC) -c -o$$@ $$($(T)_CFLAGS) $$(CFLAGS) \
		$$($(T)_INCLUDES) $$(INCLUDES) $$<

endef
