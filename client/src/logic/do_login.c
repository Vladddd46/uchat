#include "client.h"

/*
 * C
 *
 */

#define OKEY                    0
#define LOGIN_IS_EMPTY          1
#define LOGIN_FORBIDDEN_SYMBOLS 2
#define PASSWORD_IS_EMPTY       3


static int login_validator(char *login) {
    char *forbidden_symbols = " ";

    if (strlen(login) == 0)
        return LOGIN_IS_EMPTY;

    for (int i = 0; forbidden_symbols[i]; ++i) {
        if (mx_is_in_str(login, forbidden_symbols[i]))
            return LOGIN_FORBIDDEN_SYMBOLS;
    }
    return OKEY;
}

static int password_validator(char *password) {
    if (strlen(password) == 0)
        return PASSWORD_IS_EMPTY;
    return OKEY;
}

static int validate(char *login, char *password) {
    int login_status    = login_validator(login);
    int password_status = password_validator(password);

    if (login_status != OKEY) {
        // тут должно отрисовываться сообщение "неправильный синтаксис логина"
        write(2, "Input Syntax Error\n", 21);
        return 0;
    }

    if (password_status != OKEY) {
        // тут должно отрисовываться сообщение "неправильный синтаксис пароля"
        write(2, "Input Syntax Error\n", 21);
        return 0;
    }
    return 1;
}

static void send_login_packet(int socket, char *input_login, char *input_password) {
    char *login_pair = mx_strjoin("LOGIN:",    input_login);
    char *pass_pair  = mx_strjoin("PASSWORD:", input_password);
    char *packet     = json_packet_former(3, "TYPE:login_c", login_pair, pass_pair);
    char *packet_with_prefix = packet_len_prefix_adder(packet);

    send(socket, packet_with_prefix, (int)strlen(packet_with_prefix), 0);

    free(login_pair);
    free(pass_pair);
    free(packet);
    free(packet_with_prefix);
}

void do_login(GtkWidget *entryspawn, client_context_t *client_context){
    char *input_login    = (char *)gtk_entry_get_text(GTK_ENTRY(login));
    char *input_password = (char *)gtk_entry_get_text(GTK_ENTRY(Password));
    int  validate_status = validate(input_login, input_password);

    if (validate_status)
        send_login_packet(client_context->sockfd, input_login, input_password);
}
