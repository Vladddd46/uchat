# name of binary
NAME		= uchat

# # add your new dir_name and file included it (without any extansions)
# db_functions = database_init mx_database_communication opening_db

# help_functions = error json_packet_former

# logic = handle_client login_determiner login socket_list

# server = deamon listening_socket_init server
# # add dir new <dir_name> in src/<dir_name>, if you`ve created newone
# dirs		= db_functions help_functions logic server

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= inc/

SRC			= $(foreach dir, $(SRC_DIR), $(wildcard $(dir)*.c))
OBJ			= $(foreach dir, $(OBJ_DIR), $(wildcard $(dir)*.o))

# library list
LIB_DIR		= ../libs
# add lib folder in ../libs/
# (the <lib_name>.a and the ../lib/<lib_fol der_name> must be the same)
LIB_LIST	= libmx cjson
# make path to library ../libs/<lib_name>/
LIB_DIRS	= $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs)/)
# make path to ../libs/<lib_name>/<lib_name>.a
LIB_BIN		= $(join $(LIB_DIRS), $(addsuffix .a, $(LIB_LIST)))
# make path to ../libs/<lib_name>/inc
LIB_INC		= $(addsuffix $(INC_DIR), $(LIB_DIRS))


# compiler
CC			= clang
# general flags
GFLAGS		= -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic\
	-Wno-unused-command-line-argument -Wno-unused-variable \
	-Wno-unused-function -Wno-unused-parameter
# specific flags
GTK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`
GTK_SORT_FLAGS = `pkg-config --cflags gtk+-3.0`
# folder with header files
IFLAGS		= $(addprefix -I, $(LIB_INC) $(INC_DIR))

COMPILE		= $(CC) $(GFLAGS) $(IFLAGS) $(LIB_BIN)
MAKE_M		= make -sf Makefile -C
MKDIR		= mkdir -p
RM			= /bin/rm -rf

all: $(LIB_LIST) $(NAME)

print:
	@printf "$(SRC)"

$(NAME): $(OBJ_DIR) $(OBJ)
	@printf "$(OBJ)\n"
	@$(COMPILE) $(GTK_FLAGS) $(OBJ) -lmx -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(LIB_LIST):
	@$(MAKE_M) $(LIB_DIR)/$@

$(OBJ_DIR):
	@$(MKDIR) $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(COMPILE) $(GTK_SORT_FLAGS) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%) "

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR)\t   \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)
	@printf "$(OBJ_DIR)\t   \033[31;1mdeleted\033[0m\n"
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
