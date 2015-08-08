#default config
CC:= clang
AS:= as
USEREGPARM:= 1

# save / compare config
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
conf.mk:
	$(VGENT)
	$(VR)echo "C_CC := $(CC)" >conf.mk
	$(VR)echo "C_AS := $(AS)" >>conf.mk
	$(VR)echo "C_USEREGPARM := $(USEREGPARM)" >>conf.mk

-include conf.mk

ifneq ($(strip $(C_CC))_$(strip $(C_AS))_$(strip $(C_USEREGPARM)),$(strip $(CC))_$(strip $(AS))_$(strip $(USEREGPARM)))
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

CLEAN+= conf.mk

