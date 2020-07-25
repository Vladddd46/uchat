#include "server.h"

void mx_null_value_error(char *func_name) {
    char *msg = "| NULL error\n";
    mx_write_to_log(msg, 2);
    exit(1);
}
