#include "server.h"

// Checks, wether user specified input correctly.
void mx_argv_validator(int argc) {
    char *msg;

    if (argc != 2) {
        msg = "usage: ./server PORT\n";
        write(2, msg, (int)strlen(msg));
        exit(1);
    }
}
