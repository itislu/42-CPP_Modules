include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	bsp

ifdef FRACT_BITS
CPPFLAGS		:=	-D FRACT_BITS=$(FRACT_BITS)
RECOMPILE		:=	true
else
CPPFLAGS		:=
endif

MSG_PROGRESS	:=	"📐"
MSG_USAGE		?=	"Usage: ./$(NAME) <x> <y> (in unit triangle: 📐)"
COLOR_MAKE		:=	STY_YEL


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
