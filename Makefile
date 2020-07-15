NAME = uchat
SERVER_NAME = uchat_server
SERVER_DIR = server
CLIENT_DIR = client
LIBMX_DIR = libs/libmx
LIBCJSON_DIR = libs/cjson
LIBUTILS_DIR = libs/utils
LIBCRYPT_DIR = libs/crypt


MAKE_M = make -sf Makefile -C
RM = /bin/rm -rf

all:
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(CLIENT_DIR) $@

$(NAME):
	@$(MAKE_M) $(CLIENT_DIR)

$(SERVER_NAME):
	@$(MAKE_M) $(SERVER_DIR)

clean:
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(LIBMX_DIR) $@
	@$(MAKE_M) $(LIBCJSON_DIR) $@
	@$(MAKE_M) $(LIBCRYPT_DIR) $@
	@$(MAKE_M) $(LIBUTILS_DIR) $@

uninstall:
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(LIBMX_DIR) $@
	@$(MAKE_M) $(LIBCJSON_DIR) $@
	@$(MAKE_M) $(LIBUTILS_DIR) $@
	@$(MAKE_M) $(LIBCRYPT_DIR) $@

reinstall: uninstall all

.PHONY: all clean uninstall reinstall $(NAME) $(SERVER_NAME)
