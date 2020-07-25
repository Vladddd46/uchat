#include "server.h"

static char *mx_json_packet_former_from_list(char* status, char* login_to) {
        cJSON *packet = cJSON_CreateObject();
        char* packet_str = NULL;
        cJSON *json_value = cJSON_CreateString("change_password_s");

        cJSON_AddItemToObject(packet, "TYPE", json_value);
        json_value = cJSON_CreateString(login_to);
        cJSON_AddItemToObject(packet, "TO", json_value);
        json_value = cJSON_CreateString(status);
        cJSON_AddItemToObject(packet, "STATUS", json_value);
        packet_str = cJSON_Print(packet);
        
        return packet_str;
}

static char* mx_pass_validator(char *password_1, char *password_2) {
    char *forbidden_symbols = " :";

    if (mx_symbols_in_str(password_1, forbidden_symbols))
        return "forbidden_symbols";
    if (strcmp(password_1, password_2) == 0)
        return "same password as current";
    if ((int)strlen(password_1) == 0)
        return "password is empty";
    if ((int)strlen(password_1) < 8)
        return "password too short";
    return "ok";
}

static char* mx_get_current_password(char* login) {
    char sql[150];
    bzero(sql, 150);
    sqlite3 *db = mx_opening_db();
    sqlite3_stmt *res;
    char* password = NULL;
    
    sprintf(sql, "SELECT PASSWORD FROM USERS WHERE LOGIN='%s'", login);
    int check = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    mx_dberror(db, check, "SELECT PASSWORD FROM USERS WHERE LOGIN");
    sqlite3_step(res);
    password = ((char*)sqlite3_column_text(res, 0));
    sqlite3_finalize(res);
    sqlite3_close(db);
    return password;
}

char* mx_change_password(char* packet) {
    char* login = get_value_by_key(packet, "LOGIN");
    char* current_password = mx_get_current_password(login);
    char* new_password = mx_rsa_decode(get_value_by_key(packet, "TO"));
    char* status = mx_pass_validator(new_password, current_password);
    char* send_back_packet = mx_json_packet_former_from_list(status, login);

    if(!mx_strcmp(status, "ok")) {
    	sqlite3 *db = mx_opening_db();
	    char *message_error;
	    char sql[500];
	    bzero(sql, 500);
	    sprintf(sql, "UPDATE USERS SET PASSWORD = '%s' WHERE LOGIN = '%s';", new_password, login);
	    int check = sqlite3_exec(db, sql, NULL, 0, &message_error);
	    sqlite3_close(db);
    }
    return send_back_packet;
}
