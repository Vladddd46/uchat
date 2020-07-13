#include "client.h"

void do_login(GtkWidget *entryspawn, client_context_t *client_context){
char *input_login            = (char *)gtk_entry_get_text(GTK_ENTRY(login));
char *input_password         = (char *)gtk_entry_get_text(GTK_ENTRY(Password));

char *login_pair = mx_strjoin("LOGIN:", input_login);
char *pass_pair  = mx_strjoin("PASSWORD:", input_password);
char *packet = json_packet_former(3, "TYPE:login_c", login_pair, pass_pair);
char *packet_with_prefix = packet_len_prefix_adder(packet);
send(client_context->sockfd, packet_with_prefix, (int)strlen(packet_with_prefix), 0);
free(login_pair);
free(pass_pair);
free(packet);
free(packet_with_prefix);
}
