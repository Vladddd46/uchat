#include "server.h"

/*
 * Prints error msg, if status - negativ number(commonly -1)
 */
void error(char *msg, int status) {
    if (status < 0) {
        perror(msg);
        exit(1);
    }
}
