# ***************************** CONFIGURATION ******************************** #

NAME			:=	bsp

ifdef FRACT_BITS
CPPFLAGS		:=	-D FRACT_BITS=$(FRACT_BITS)
RECOMPILE		:=	true
else
CPPFLAGS		:=
endif

MSG_PROGRESS	:=	"📐"
MSG_USAGE		?=	"\nUsage: ./$(NAME) <x> <y> (in unit triangle: 📐)\n"
COLOR_MAKE		:=	STY_YEL

include				../global.mk
