#include "server.h"

// Prints db msg error on stderr.
void mx_db_msg_error(int status, char *msg_error) {
    if(status != SQLITE_OK) {
        mx_write_to_log(msg_error, 2);
        sqlite3_free(msg_error);
    }
}
