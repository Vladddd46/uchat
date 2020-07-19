#include "server.h"

/*
 * Checks status of sqlite requests.
 * In case of error, prints error msg.
 * Closes db and exits programm.
 */
void dberror(sqlite3 *db, int status, char *msg) {
    if (status != SQLITE_OK) {
        write(2, msg, (int)strlen(msg));
        write(2, "\n", 1);
        sqlite3_close(db); 
        exit(1);
    }
}
