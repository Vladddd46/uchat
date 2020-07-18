#include "server.h"

void mx_null_value_error(char *func_name) {
    char *msg = "login_system error| NULL error\n";
    write(2, msg, (int)strlen(msg));
    exit(1);
}
