#include <iostream>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>

static int mx_atoi_add(const char* str) { 
    int result = 0; 

    for (int i = 0; *(str + i) != '\0'; ++i) 
        result = result * 10 + *(str + i) - '0'; 
    return result; 
} 

static int mx_atoi(const char * str) {
	int str_len = strlen(str);
    char *num_str = (char *)malloc(str_len * sizeof(char));
    int index = 0;
    char ch;

    if (!str)
        return 0;
    for (int i = 0; i < str_len; ++i) {
        ch = *(str + i);
        if (ch == 0) {
            *(num_str + index) = 0;
            break;
        }
        if (isdigit(ch))
            *(num_str + index++) = ch;
    }
    *(num_str + index) = 0;
    int ret = mx_atoi_add((const char *)num_str);
    free(num_str);
    return ret;
}

/*
    * Changes terminal`s mode to raw.
*/
static void mx_enable_raw_mode(struct termios orig_termios) {
    struct termios raw = orig_termios;

    tcgetattr(0, &orig_termios);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSAFLUSH, &raw);
}

/*
    * Changes terminal`s mode to original.
*/
static void mx_disable_raw_mode(struct termios orig_termios) {
    tcsetattr(0, TCSAFLUSH, &orig_termios);
}

static char *mx_strnew(int size) {
	int sized = size * 2;
    char *memory = (char*)malloc(sized + 1);

    if (memory == NULL)
        return NULL;
    for (int i = 0; i < sized + 1; i++)
        *(memory + i) = '\0';
    return memory;
}

int main() {
    struct termios orig_termios;
    char buff = '\0';
    int size = 0;
    char* input = mx_strnew(4096);
    int kvadrat;

    tcgetattr(0, &orig_termios);
    mx_enable_raw_mode(orig_termios);
    std::cout << "q - to escape\nType number";
    while(buff != 113) {
        std::cin >> buff;
        system("clear");
        if(buff == 127) {
        	size--;
        	if(size < 0)
        		size = 0;
        	*(input + size) = '\0';
        }
        *(input + size)= buff;
        if(buff != 127)
            size++;
        kvadrat = mx_atoi(input) * mx_atoi(input);
        std::cout << "\r" << input << " kvadrat is - " 
        << kvadrat;
    }
    free(input);
    mx_disable_raw_mode(orig_termios);
    return 0;
}
