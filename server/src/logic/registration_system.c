#include "server.h"

// static char *msg_former(int status) {
//     char *msg = NULL;

//     if (status == 1)
//         msg = "MSG:OK";
//     else if (status == 2)
//         msg = "MSG:User with such login is already exists";
//     else if (status == 3)
//         msg = "MSG:User with such nickname is already exists";
//     return msg;
// }

// static char *status_converter(int return_status) {
//     if (return_status == 1)
//         return "STATUS:true";
//     return "STATUS:false";
// }

static char* mx_insert_all_args(char* login, char* password, char* nickname) {
	char* request = mx_strjoin("INSERT INTO USERS (LOGIN, PASSWORD, NICKNAME) VALUES('", login);

    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, nickname);
    request = mx_strjoin(request, "', '");
    request = mx_strjoin(request, password);
    request = mx_strjoin(request, "');");
    // printf("%s", request);
    return request;
}

static int mx_add_user(const char *str, char* login, char* password, char* nickname) {
    sqlite3 *db;
    char *message_error;
    int exit = sqlite3_open(str, &db);
    char* sql = mx_insert_all_args(login, password, nickname);

    exit = sqlite3_exec(db, sql, NULL, 0, &message_error);
    if(exit != SQLITE_OK) {
    	printf("Error insert");
    	sqlite3_free(message_error);
    }
    return 0;
}
char *registration_system(char *packet) {
    char *login    = get_value_by_key(packet, "LOGIN");
    char *password = get_value_by_key(packet, "PASSWORD");
    char *nickname = get_value_by_key(packet, "NICKNAME");

    int  return_status     = mx_add_user("../db_functions/uchat.db", login, password, nickname);
    // char *status           = status_converter(return_status);
    // char *msg              = msg_former(return_status);

    // char *sendback_packet  = json_packet_former(2, "TYPE:reg_s", status, msg);
    char *sendback_packet = json_packet_former(3, "TYPE:reg_s", "STATUS:true", "MSG:OK"); // Debug.
    
    return sendback_packet;
}
