#include "client.h"

 char *mx_get_time() {
    time_t rawtime;
    struct tm * timeinfo;
    char *date = NULL;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    date = asctime (timeinfo);
    return date;
}
