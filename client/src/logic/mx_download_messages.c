#include "client.h"

void download_messages(GtkWidget *widget, gpointer data){
  
    cJSON *packet = cJSON_CreateObject();
    char  *packet_str = NULL;
    cJSON *type = cJSON_CreateString((char*)"msg_c");

    char *chat_id_str = (char*)mx_itoa(client_context->indexrow + 1);
    if (chat_id_str == NULL)
        mx_null_error("26: download_messages");
    cJSON *chat_id = cJSON_CreateString(chat_id_str);
    free(chat_id_str);

    char *from_str = (char*)mx_itoa(client_context->counter);
    if (from_str == NULL)
        mx_null_error("31: download_messages");
    cJSON *from = cJSON_CreateString(from_str);

    char *to_str = (char*)mx_itoa(client_context->counter + 15);
    if (to_str == NULL)
        mx_null_error("36: download_messages");
    cJSON *to = cJSON_CreateString(to_str);

    char *chat_name_str = (char *)client_context -> username;
    if (chat_name_str == NULL)
        mx_null_error("41: download_messages");
    cJSON *chat_name = cJSON_CreateString(chat_name_str);


    char *to_user_str = (char*)client_context -> username;
    if (to_user_str == NULL)
        mx_null_error("46: download_messages");
    cJSON *to_user = cJSON_CreateString(to_user_str);


    char *chat_id_sql_str = (char*)client_context->mas[client_context->indexrow];
    if (chat_id_sql_str == NULL)
        mx_null_error("52: download_messages");
    cJSON *chat_id_sql = cJSON_CreateString(chat_id_sql_str);
    
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "CHATID", chat_id);
    cJSON_AddItemToObject(packet, "FROMMSG", from);
    cJSON_AddItemToObject(packet, "TOMSG", to);
    cJSON_AddItemToObject(packet, "CHATNAME", chat_name);
    cJSON_AddItemToObject(packet, "TO", to_user);
    cJSON_AddItemToObject(packet, "CHATIDFROMDB", chat_id_sql);

    packet_str         = mx_string_copy(cJSON_Print(packet));
    char *packet_str1 =  packet_len_prefix_adder(packet_str);
    if (packet_str1 == NULL)
        mx_null_error("66: download_messages");

    send(client_context->sockfd, mx_strdup(packet_str1), (int)strlen(packet_str1), 0);
    free(packet_str);
    free(packet_str1);
}
