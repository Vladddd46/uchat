#include "client.h"

void mx_back_to_menu(GtkWidget *back, client_context_t *client_context){
    gtk_widget_destroy(grid);
    mx_main_menu(); 
}
