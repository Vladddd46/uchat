NAME = uchat
SERVER_DIR = server
CLIENT_DIR = client
LIBMX_DIR		= libs/libmx
LIBCJSON_DIR	= libs/cjson


MAKE_M = make -sf Makefile -C
RM = /bin/rm -rf

all: $(LIBMX_DIR) $(LIBCJSON_DIR) $(SERVER_DIR) $(CLIENT_DIR)

$(SERVER_DIR):
	@$(MAKE_M) $@

$(CLIENT_DIR):
	@$(MAKE_M) $@

$(LIBMX_DIR):
	@$(MAKE_M) $@

$(LIBCJSON_DIR):
	@$(MAKE_M) $@

clean:
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(LIBMX_DIR) $@
	@$(MAKE_M) $(LIBCJSON_DIR) $@

uninstall:
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(LIBMX_DIR) $@
	@$(MAKE_M) $(LIBCJSON_DIR) $@

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
