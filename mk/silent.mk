V?= 0

ifeq ($(V),1)
VCC:=
VAS:=
VDEP:=
VLD:=
VAR:=
VCCLD:=
VMD:=
VGEN:=
VGENT:=
VR:=
else
VCC=	@echo "   [CC]   $@"
VAS=	@echo "   [AS]   $@"
VDEP=	@echo "   [DEP]  $@"
VLD=	@echo "   [LD]   $@"
VAR=	@echo "   [AR]   $@"
VCCLD=	@echo "   [CCLD] $@"
VMD=	@echo "   [MD]   $@"
VGEN=	@echo "   [GEN]  $@"
VGENT=	@echo "   [GEN]  $@: $(VTAGS)"
VR:=	@
endif

