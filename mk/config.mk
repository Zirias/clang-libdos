#default config
CC:= clang
AS:= as
USEREGPARM?= 1
USEARGV?= 1

# save / compare config
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
conf.mk:
	$(VGENT)
	$(VR)echo "C_CC := $(CC)" >conf.mk
	$(VR)echo "C_AS := $(AS)" >>conf.mk
	$(VR)echo "C_USEREGPARM := $(USEREGPARM)" >>conf.mk
	$(VR)echo "C_USEARGV := $(USEARGV)" >>conf.mk

-include conf.mk

ifneq ($(strip $(C_CC))_$(strip $(C_AS))_$(strip $(C_USEREGPARM))_$(strip $(C_USEARGV)),$(strip $(CC))_$(strip $(AS))_$(strip $(USEREGPARM))_$(strip $(USEARGV)))
.PHONY: conf.mk
endif
endif
endif

CFLAGS?= -Wall -Wextra -pedantic
ifeq ($(USEREGPARM),1)
CFLAGS+= -mregparm=3
VTAGS+= [REGPARM]
else
VTAGS+= [STACKPARM]
endif
ifeq ($(USEARGV),1)
VTAGS+= [ARGV]
else
CFLAGS+= -DNOARGV
VTAGS+= [NOARGV]
endif

CLEAN+= conf.mk

