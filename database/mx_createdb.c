#include "db.h"

int mx_createdb(const char* str) {
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(str, &DB);
    if(exit != SQLITE_OK) {
    	printf("Error to create a table ");
    }
    sqlite3_close(DB);
    return 0;
}
