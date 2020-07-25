#include "client.h"

gboolean create_message_system(void *data){
    char *message_from_user = get_text_of_textview(newmessedgentry);
    char *processed_msg_from_user = mx_change_offensive_words(message_from_user);
    char *all_users = client_context->allusers;
    char  *packet_str = NULL;
    cJSON *packet = cJSON_CreateObject();
    cJSON *type   = cJSON_CreateString("add_msg_c");
    cJSON *type2  = cJSON_CreateString("string");
    char *current_time = mx_get_time();
    cJSON *time        = cJSON_CreateString(current_time);
    cJSON *msg         = cJSON_CreateString(processed_msg_from_user);
    cJSON *allusers    = cJSON_CreateString(all_users);
    cJSON *message_id  = cJSON_CreateString("0");
    int chat_id_client = client_context->indexrow;
    cJSON *chat_id     = cJSON_CreateString(client_context->mas[client_context->indexrow]);
    cJSON *username    = cJSON_CreateString(client_context -> username);
    cJSON_AddItemToObject(packet, "TYPE", type);
    cJSON_AddItemToObject(packet, "TYPE2", type2);
    cJSON_AddItemToObject(packet, "MESSAGEID", message_id);
    cJSON_AddItemToObject(packet, "TIME", time);
    cJSON_AddItemToObject(packet, "TO", allusers);
    cJSON_AddItemToObject(packet, "MESSAGE", msg);
    cJSON_AddItemToObject(packet, "CHATID", chat_id);
    cJSON_AddItemToObject(packet, "SENDER", username);
    packet_str = mx_string_copy(cJSON_Print(packet));
    char *packet_str1 =  packet_len_prefix_adder(packet_str);
    printf(">>>>>>>>>>>>>PACKETOUT%s\n",packet_str1 );
    send(client_context->sockfd, packet_str1, (int)strlen(packet_str1), 0);
    free(packet_str);
    free(packet_str1);
    return 0;
}
