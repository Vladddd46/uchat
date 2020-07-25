#include "client.h"
        
void mx_switchlanguage_system(GtkSwitch *widget,
               gboolean   state,
               gpointer   user_data){
    if (state == TRUE){
        system("open ./media/gimn.mp3");
        client_context->Ukraine = TRUE;
    }
    if (state == FALSE) {
        client_context->Ukraine = FALSE;
    }
}        
