#compiler name
CC 		=	clang

#binary name
NAME	=	uchat_server

#general compiler flags
CFLG_G	=	-std=c11 $(addprefix -W, all, error, pedantic, extra)

#specific compiler flags (add some, if you need it)
CFGG_S	=	-lsqlite3 -lpthread

SRC_DIR = src/
OBJ_DIR	= obj/
LIB_DIR = ../libmx/

#add dir new <dir_name> in src/<dir_name>, if you`ve created newone
dirs	=	db_functions help_functions logic server

#add your new dir_name and file included it (without any extansions)
db_functions = database_init mx_database_communication opening_db

help_functions = error json_packet_former

logic = handle_client login_determiner login socket_list

server = deamon listening_socket_init server

#making filenames for compiling
FILES	=	$(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

#make src file
SRC		=	$(FILES:%=$(SRC_DIR)%.c)
#make obj file
OBJD	=	$(FILES:%=$(OBJ_DIR)%.o)
#ADD LIB!!!!

all: `$(NAME)

$(NAME):
	clang $(CFLG) src/*/*.c -I inc/ -I ../libs/cjson/inc  -I ../libs/libmx/inc/ -lpthread ../libs/libmx/libmx.a ../libs/cjson/cJSON.a -o server
