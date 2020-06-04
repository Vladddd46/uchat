#include "uchat.h"

void error(char *msg, int status) {
    if (status < 0) {
        perror(msg);
        exit(1);
    }
}
