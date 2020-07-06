#include "utils.h"

// Determines how much time select will wait for incomming connections.
struct timeval wait_time(int sec, int msec) {
    struct timeval tv;
    tv.tv_sec  = sec; // seconds.
    tv.tv_usec = msec; // mili-seconds.
    return tv;
}
