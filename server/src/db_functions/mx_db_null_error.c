#include "server.h"

void mx_db_null_error(char *func_name) {
    char *msg = "mx_find_user| DB request null error";
    write(2, msg, (int)strlen(msg));
    exit(1);
}

