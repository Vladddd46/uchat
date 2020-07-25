#include "server.h"

/*
 * Checks status of sqlite requests.
 * In case of error, prints error msg.
 * Closes db and exits programm.
 */
void mx_dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        mx_write_to_log(msg, 2);
        sqlite3_close(db); 
        exit(1);
    }
}
