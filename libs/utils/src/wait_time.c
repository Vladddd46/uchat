#include "utils.h"

// Determines how much time select will wait for incomming connections.
struct timeval wait_time() {
    struct timeval tv;
    tv.tv_sec  = 1; // seconds.
    tv.tv_usec = 0; // mili-seconds.
    return tv;
}
