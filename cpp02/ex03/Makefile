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

include				$(shell git rev-parse --show-toplevel)/Makefiles/global.mk
