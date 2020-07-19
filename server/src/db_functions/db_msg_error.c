#include "server.h"

// Prints db msg error on stderr.
void db_msg_error(int status, char *msg_error) {
    if(status != SQLITE_OK) {
        write(2 , msg_error, (int)strlen(msg_error));
        sqlite3_free(msg_error);
    }
}
