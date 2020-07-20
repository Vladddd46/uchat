NAME	=	utils.a
CFLG	=	-std=c11
SRCD	=	src
INCD	=	inc
OBJD	=	obj
INC		=	utils.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		=	get_value_by_key.c\
			json_packet_former.c\
			error.c\
			packet_len_prefix_adder.c\
			wait_time.c\
			packet_receive.c\
			mx_send.c\
			mx_change_offensive_words.c\
			
SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(CFLG) -c $< -o $@ -I$(INCD) -I ../libmx/inc -I ../cjson/inc -I ../crypt/inc -I ../libmx/libmx.a -I ../cjson/cJSON.a -I ../crypt/crypt.a
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install
