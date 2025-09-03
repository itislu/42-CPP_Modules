include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	PmergeMe
MSG_PROGRESS	:=	"🔀"
COLOR_MAKE		=	$(STY_BLU)
MSG_USAGE		?=	"Usage: ./$(NAME) [-m|--more-types] [-n|--no-before-after] <positive_number...>"
LIBS_LOCAL		=	$(LIB_ROOT_DIR)/libftpp/libftpp.a


#	Functions

define IS_NUMERIC
$(shell echo "$(1)" | grep -q -E '^[0-9]+$$' && echo 1 || echo 0)
endef

ifneq (, $(shell command -v shuf))
define GENERATE_RANDOM_NUMBERS
$(shell shuf -i 0-150000 -n $(1) | tr '\n' ' ')
endef
else
define GENERATE_RANDOM_NUMBERS
$(shell jot -r $(1) 0 150000 | tr '\n' ' ')
endef
endif


#	Target to run with N amount of random numbers (no duplicates).
#	MODE can be used to combine other targets.
#	ARGS can be used to add options to the program.
#	Usage: make run-<N> [MODE=...] [ARGS=...]

RUN_NUM			:=	$(patsubst run-%,%,$(MAKECMDGOALS))
ifeq (1, $(call IS_NUMERIC,$(RUN_NUM)))
.PHONY			:	$(RUN_NUM)
override ARGS	:=	$(ARGS) $(call GENERATE_RANDOM_NUMBERS,$(RUN_NUM))
$(MAKECMDGOALS)	:	run
endif


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
