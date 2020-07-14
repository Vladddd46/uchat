#include "client.h"

client_context_t *client_context;

void registration_system(int socket, char *packet) {
    char *status = get_value_by_key(packet, "STATUS");
    client_context->username = get_value_by_key(packet,"TO");

    if (!strcmp(status, "success")) {
        gdk_threads_add_idle_full(G_PRIORITY_HIGH_IDLE, draw_message_menu, NULL, 0);
    }
    else {
        printf("%s\n", status);
       /* Денис:
        * Тут регестрация прошла неуспешно.
        * Пользователю должно вывестись уведомление о неуспешной регестрации
        * причина неуспешной регестрации хранится в char *status (printf(status))
        */
    }
}
