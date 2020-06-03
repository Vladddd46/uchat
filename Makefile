NAME=server
COMPILER=clang

all:
	$(COMPILER) -I inc/ src/*.c src/libmx/*.c -o $(NAME)
