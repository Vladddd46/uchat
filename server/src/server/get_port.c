#include "server.h"

/*
 * Checks, whather user sepcified port number correctly.
 * If wrong port number - error msg prints + exit.
 * In case of success  - returns <int> port number.
 */
int mx_get_port(char **argv) {
    int port = atoi(argv[1]);
    char *msg;

    if (port == 0) {
    	mx_write_to_log("Invalid port number\n", 2);
        exit(1);
    }
    return port;
}
