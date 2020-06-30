#include "server.h"

sqlite3 *opening_db() {
    sqlite3 *db;
    int status = sqlite3_open("uchat.db", &db);
    if (status != SQLITE_OK) {
        char *msg = "Can`t open database.\n";
        write(2, msg, (int)strlen(msg));
        sqlite3_close(db); 
        exit(1);
    }
    return db;
}
