#default config
USECC?= gcc
USEAS?= as
USEREGPARM?= 1
USEARGV?= 1

# save / compare config
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean)
conf.mk:
	$(VGENT)
	$(VR)echo "C_USECC := $(USECC)" >conf.mk
	$(VR)echo "C_USEAS := $(USEAS)" >>conf.mk
	$(VR)echo "C_USEREGPARM := $(USEREGPARM)" >>conf.mk
	$(VR)echo "C_USEARGV := $(USEARGV)" >>conf.mk

-include conf.mk

ifneq ($(strip $(C_USECC))_$(strip $(C_USEAS))_$(strip $(C_USEREGPARM))_$(strip $(C_USEARGV)),$(strip $(USECC))_$(strip $(USEAS))_$(strip $(USEREGPARM))_$(strip $(USEARGV)))
.PHONY: conf.mk
endif
endif
endif

ifneq ($(strip $(USECC)),)
CC:= $(USECC)
endif
ifneq ($(strip $(USEAS)),)
AS:= $(USEAS)
endif
VTAGS+= [$(CC)]

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

