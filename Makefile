CLN		=	./client
SRV		=	./server 
OBJC	=	client/obj
OBJS	=	server/obj
NAMECLIENT	=	/client
NAMESERVER	=	./server/server

LMXD	=	./libs/libmx
MKCL	=	make\
			clean\

all:
	@make -sC $(CLN)
	@make -sC $(SRV)

clean:
	@make -sC $(LMXD) $@
	@rm -rf $(OBJC)
	@printf "$(OBJC)\t   \033[31;1mdeleted\033[0m\n"
	@rm -rf $(OBJS)
	@printf "$(OBJS)\t   \033[31;1mdeleted\033[0m\n"

uninstall:
	@make -sC $(LMXD) $@
	@rm -rf $(CLN)$(NAMECLIENT) $(NAMESERVER)

reinstall: uninstall all
