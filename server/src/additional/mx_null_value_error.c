#include "server.h"

void mx_null_value_error(char *func_name) {
    char *msg = "| NULL error\n";
    write(2, func_name, (int)strlen(func_name));
    write(2, msg, (int)strlen(msg));
    exit(1);
}
