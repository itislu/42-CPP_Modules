include				$(shell git rev-parse --show-toplevel)/Makefiles/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME				:=	btc
MSG_PROGRESS		:=	"🪙 "
COLOR_MAKE			=	$(STY_YEL)
LIBS_LOCAL			=	$(LIB_ROOT_DIR)/libftpp/libftpp.a
DEFAULT_DATA_FILE	?=	test_data/data.csv
CPPFLAGS			:=	-D DEFAULT_DATA_FILE='"$(DEFAULT_DATA_FILE)"'
MSG_USAGE			?=	"Usage: ./$(NAME) <input_file> [data_file=$(DEFAULT_DATA_FILE)]"


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
