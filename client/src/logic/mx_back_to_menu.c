#include "client.h"

void back_to_menu(GtkWidget *back, client_context_t *client_context){
    gtk_widget_destroy(grid);
    main_menu(); 
}
