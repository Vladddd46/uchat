CC = clang
NAME = libmx.a

file = get_file_length file_to_str read_line

json = cJSON

list = clear_list create_list create_node delete_list foreach_list_reverse \
	foreach_list get_index list_to_array pop_back pop_front pop_index \
	push_back push_front push_index

memory = memdup memrchr

print = print_strarr print_unicode printchar printnum printstr printstrlen \
	printunum

string = count_substr count_words del_extra_spaces del_strarr get_char_index \
	get_substr_index lltoa_s lltoa replace_substr str_reverse strdel strdup \
	strjoin strndup strnew strsplit strtrim ulltoa_s ulltoa ulltoh_s ulltoh

utils = factorial foreach isprime numlen sigma sum_digits swap unumlen

dirs = file json list memory print string utils
FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/mx_%))

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter

LFLAGS = -Iinc

# CFLAGS = -Ofast -march=native -fomit-frame-pointer -flto

CFLAGS = -O0 -g3 -glldb -ftrapv -fno-omit-frame-pointer -fsanitize=address \
	-fsanitize=undefined

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
PRINT = printf
MKDIR = mkdir -p
AR = ar rcs
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
K = \033[K

all: $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(PRINT) "$K$G ARCHIVING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
	@$(AR) $(NAME) $(OBJ)
	@$(PRINT) "$K"

clean:
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
