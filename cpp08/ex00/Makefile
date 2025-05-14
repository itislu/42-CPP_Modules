include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME					:=	easyfind
MSG_PROGRESS			:=	"🔎"
COLOR_MAKE				=	$(STY_BLU)
LIBS_LOCAL				=	$(LIB_ROOT_DIR)/libftpp/libftpp.a
DEFAULT_CONTAINER_SIZE	?=	64
MSG_USAGE				?=	"Usage: ./$(NAME) [container_size=$(DEFAULT_CONTAINER_SIZE)]"
CPPFLAGS				:=	-D DEFAULT_CONTAINER_SIZE=$(DEFAULT_CONTAINER_SIZE)


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
