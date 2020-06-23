NAME	=	server

CFLG	=	-std=c11 -lsqlite3

SRCD	=	src
INCD	=	inc
OBJD	=	obj

LMXD	=	../libs/libmx
LMXA:=	$(LMXD)/libmx.a
LMXI:=	$(LMXD)/$(INCD)

INC		=	server.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		=	error.c\
			server.c\
			mx_client_process.c\
			database_init.c\

SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: $(NAME)

$(NAME):
	clang $(CFLG) src/*/*.c -I inc/ -I ../libs/cjson/inc  -I ../libs/libmx/inc/ -lpthread ../libs/libmx/libmx.a ../libs/cjson/cJSON.a -o server
