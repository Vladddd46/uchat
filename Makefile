CLN		=	./client
SRV		=	./server
LIBMX		= 	./libs/libmx
CJSON 		= 	./libs/cjson

all: clean install

install:
	@make -sC $(LIBMX)
	@make -sC $(CJSON)
	@make -sC $(CLN)
	@make -sC $(SRV)

clean:
	rm -rf ./server/server
	rm -rf ./client/client
	rm -rf ./libs/libmx/libmx.a
	rm -rf ./libs/libmx/obj
	rm -rf ./libs/cjson/cJSON.a
	rm -rf ./libs/cjson/obj