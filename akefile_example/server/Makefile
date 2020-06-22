CC = clang
LIB = libmx.a
NAME = uchat_server

base = main

init = daemonize init_info sockets_initialize sockets_initialize_2

sockets = handle_incoming_data handle_new_connection loop \
	receive_message send_message shutdown signals message_handler \
	func_response_db_1 func_response_db_2

sql = authorization check_error close_db create_tables init_db \
	receive_message registration create_personal_chat get_present_chat \
	change_password send_message

utils = initialize_zero message_on_email

dirs = base init sockets sql utils
FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = ../libmx/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)
LIB_PATH = $(LIB_DIR)$(LIB)

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter

LFLAGS = -Iinc -I$(LIB_DIR)inc -I/usr/local/opt/openssl/include \
	-L/usr/local/opt/openssl/lib -lssl -lcrypto -lsqlite3

# CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto

CFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address \
	-fsanitize=undefined

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
EXEC_IT = make -sf Makefile
EXEC_LD = $(EXEC_IT) -C $(LIB_DIR)
PRINT = printf
MKDIR = mkdir -p
RM = /bin/rm -rf
TARGET = debug

R = \033[1;91m
G = \033[1;92m
Y = \033[1;93m
B = \033[1;94m
M = \033[1;95m
C = \033[1;96m
S = \033[38;5;45;1m
D = \033[0m
F = \033[5m
A = \033[A
K = \033[K

all: $(LIB) $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

$(LIB):
	@$(EXEC_LD)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
	@$(COMPILE) $(CFLAGS) $(LIB_PATH) $(OBJ) -o $(NAME)
	@$(PRINT) "$K"

clean:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR) $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
