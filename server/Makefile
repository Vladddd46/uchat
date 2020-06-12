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

all: $(LMXD) $(NAME)

$(FILE:a/%=%)

#install: $(LMXA) $(NAME)

$(NAME): $(LMXA) $(OBJS)
	@clang $(CFLG) $(OBJS) -L$(LMXD) -lsqlite3 -lmx -o $@
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD) -I$(LMXI)
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LMXD): $(LMXA)

$(LMXA):
	@make -sC $(LMXD)

clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@make -sC $(LMXD) $@
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all