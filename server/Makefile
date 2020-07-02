# name of binary
NAME		= uchat_server

# main dir for source files
SRC_DIR		= src/
# main dir for obj files
OBJ_DIR		= obj/
# main dir for header files
INC_DIR		= inc/
# list of subdirs in src/
DIRS		= $(notdir $(wildcard $(SRC_DIR)*))
# list of only source C-files without extansions
FILES		= $(foreach dir, $(DIRS), $(basename $(wildcard \
			  $(SRC_DIR)$(dir)/*.c)))
# adding extansions .c to FILES
SRC			= $(FILES:%=%.c)
# adding extansions .o to FILES
OBJ			= $(SRC:src/%.c=$(OBJ_DIR)%.o)
# list of header files
INC_H		= $(wildcard $(INC_DIR)*.h)

# main dir with any libraries
LIB_DIR		= ../libs
# list of all names of libraries in LIB_DIR
LIB_LIST	= $(notdir $(wildcard $(LIB_DIR)/*))
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
CFLAGS		= -lsqlite3 -lpthread
# folder with header files
IFLAGS		= $(addprefix -I, $(LIB_INC) $(INC_DIR))

COMPILE		= $(CC) $(GFLAGS) $(IFLAGS) $(CFLAGS) $(LIB_BIN)
MAKE_M		= make -sf Makefile -C
MKDIR		= mkdir -p
RM			= /bin/rm -rf

# checking if libs are up to date
all: $(LIB_LIST) $(NAME)

# LIB_BIN for libs dependency
$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_BIN)
	@$(COMPILE) $(OBJ) -lmx -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

# make for all libs
$(LIB_LIST): $(LIB_DIRS)
	@$(MAKE_M) $(LIB_DIR)/$@

# make dirs for obj files
$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

# comling obj files
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H)
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%) "

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR)\t   \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
