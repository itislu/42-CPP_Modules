# ***************************** CONFIGURATION ******************************** #

NAME			:=	fixed

ifdef FRACT_BITS
CPPFLAGS		:=	-D FRACT_BITS=$(FRACT_BITS)
RECOMPILE		:=	true
else
CPPFLAGS		:=
endif

MSG_PROGRESS	:=	"🧮"
MSG_USAGE		?=	"Usage: ./$(NAME)"
COLOR_MAKE		:=	STY_GRE

include				$(shell git rev-parse --show-toplevel)/global.mk
