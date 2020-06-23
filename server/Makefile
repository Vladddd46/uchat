CC = clang
LIB = libmx.a
NAME = uchat_server

# add your new dir_name and file included it (without any extansions)
db_functions = database_init mx_database_communication opening_db

help_functions = error json_packet_former

logic = handle_client login_determiner login socket_list

server = deamon listening_socket_init server
# add dir new <dir_name> in src/<dir_name>, if you`ve created newone
dirs = db_functions help_functions logic server

FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

SRC_DIR = src/
OBJ_DIR = obj/
# library list
LIB_DIR	= ../libs
# add lib folder in ../libs/ (the <lib_name>.a and the ../lib/<lib_folder_name> must be the same)
LIB_LIST = libmx cjson
# make path to library
LIB_DIRS = $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs))
# make path to ../libs/<lib_name>/<lib_name>.a
LIB_BIN = $(foreach libbin, $(LIB_DIRS), ())

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)
LIB_PATH = $(LIB_DIR)$(LIB)

WFLAGS = -Wall -Wextra -Werror -Wpedantic

LFLAGS = -I inc -I

CFLAGS = -lsqlite3

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
EXEC_IT = make -sf Makefile
EXEC_LD = $(EXEC_IT) -C $(LIB_DIR)
MKDIR = mkdir -p
RM = /bin/rm -rf
TARGET = debug

all: $(LIB_LIST) $(NAME)

print:
	@printf "$(LIB_DIRS)"

$(LIB_LIST):
	@make -sf Makefile -C $(LIB_DIR)/$@

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%) "

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(COMPILE) $(LIB_PATH) $(OBJ) -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"


clean:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR) $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
