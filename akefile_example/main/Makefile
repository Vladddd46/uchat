CC = clang

CLIENT = uchat
SERVER = uchat_server

LIB_DIR = libmx/
CLIENT_DIR = client/
SERVER_DIR = server/

CLIENT_PATH = $(CLIENT_DIR)$(CLIENT)
SERVER_PATH = $(SERVER_DIR)$(SERVER)

CLIENT_SRC = $(wildcard $(CLIENT_DIR)src/**/*.c)
SERVER_SRC = $(wildcard $(SERVER_DIR)src/**/*.c)

EXEC_IT = make -sf Makefile
EXEC_LD = $(EXEC_IT) -C
RM = /bin/rm -rf

all:
	@$(EXEC_IT) $(CLIENT)
	@$(EXEC_IT) $(SERVER)

$(CLIENT): $(CLIENT_SRC)
	@$(EXEC_LD) $(CLIENT_DIR)
	@cp $(CLIENT_PATH) .

$(SERVER): $(SERVER_SRC)
	@$(EXEC_LD) $(SERVER_DIR)
	@cp $(SERVER_PATH) .

clean:
	@$(EXEC_LD) $(LIB_DIR) clean
	@$(EXEC_LD) $(CLIENT_DIR) clean
	@$(EXEC_LD) $(SERVER_DIR) clean

uninstall:
	@$(RM) $(CLIENT) $(SERVER)
	@$(EXEC_LD) $(LIB_DIR) uninstall
	@$(EXEC_LD) $(CLIENT_DIR) uninstall
	@$(EXEC_LD) $(SERVER_DIR) uninstall

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
