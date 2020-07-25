#include "client.h"
        
void switchlanguage_system(GtkSwitch *widget,
               gboolean   state,
               gpointer   user_data){
    if (state == TRUE){
        printf("%s\n","UKraine" );
        system("open ./media/gimn.mp3");
        client_context->Ukraine = TRUE;
    }
    if (state == FALSE) {
        client_context->Ukraine = FALSE;
        printf("%s\n","English" ); 
    }
}        
