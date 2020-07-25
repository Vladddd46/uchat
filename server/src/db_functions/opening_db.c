#include "server.h"

sqlite3 *mx_opening_db() {
    sqlite3 *db;
    int status = sqlite3_open("uchat.db", &db);
    if (status != SQLITE_OK) {
        mx_write_to_log("Can`t open database.\n", 2);
        sqlite3_close(db); 
        exit(1);
    }
    return db;
}
