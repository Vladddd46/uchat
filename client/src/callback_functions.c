#include "client.h"

void back_to_menu(GtkWidget *back, int sockfd){
gtk_widget_destroy(grid);
main_menu(sockfd);
}