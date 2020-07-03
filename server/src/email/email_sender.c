#include "server.h"

static void mail_subj(char cases, char **subj) {
    switch (cases) {
        case 'r':
            sprintf(*subj, "Greatings from uChat team");
            break;
        case 'p':
            sprintf(*subj, "Your new password for uChat account");
        default:
            return;
    }
}

static void mail_text(char *pass, char cases, char **text) {
    if (cases == 'r') {
        sprintf(*text, "Wellcome to uchat");
    }
    if (cases == 'p') {
        sprintf(*text, "Your new password: %s\nDo not forget to change \
                it.\n", pass);
    }
}

/*
 * Funcion send email to user. While using it, have to specify variable
 * cases in order with:
 * 'r' - send email after registration (variable pass can be random)
 * 'p' - send email to send new passwor
 */

void mx_send_email_to_user(char *addr, char *pass, char cases) {
    char *cmd = malloc(sizeof(char) * 1024);
    char *text = malloc(sizeof(char) * 1024);
    char *subj = malloc(sizeof(char) * 128);

    mail_subj(cases, &subj);
    mail_text(pass, cases, &text);
    sprintf(cmd, "mail -s \"%s\" %s <<< \"%s\"", subj, addr, text);
    system(cmd);
    free(cmd);
    free(text);
    free(subj);
    return;
}
