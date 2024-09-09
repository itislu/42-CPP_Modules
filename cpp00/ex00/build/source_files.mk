# Initialize SRC
SRC		:= $(SRC)

# Main:
DIR		:=	./
SRC		+=	$(addprefix $(DIR), \
            megaphone.cpp \
)
