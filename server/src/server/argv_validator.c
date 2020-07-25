#include "server.h"

// Checks, wether user specified input correctly.
void mx_argv_validator(int argc) {
    char *msg;

    if (argc != 2) {
        mx_write_to_log("usage: ./server PORT\n", 2);
        exit(1);
    }
}
