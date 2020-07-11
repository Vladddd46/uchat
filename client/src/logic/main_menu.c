#include "client.h"
client_context_t *client_context;

void mx_show_dialog(GtkWidget *parent, char *message) {
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window),
        flags,
        GTK_MESSAGE_WARNING,
        GTK_BUTTONS_OK,
        "\n%s",
        message
    );

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void main_menu() {
    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 350,175);

    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokeball.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 128,128, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

     
    // GtkWidget * imagemorph = gtk_image_new_from_file("./morf.gif");
    // gtk_fixed_put(GTK_FIXED (fixed), imagemorph, 0,0);
    // gtk_widget_set_size_request(imagemorph, 1024,768);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login),"Login");
    gtk_widget_set_name(login,"login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 100, 1, 1);

    Password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password),"Password");
    gtk_widget_set_name(Password,"Password");
    gtk_grid_attach(GTK_GRID(grid), Password, 1, 101, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(Password),FALSE);
    g_signal_connect(Password, "activate", G_CALLBACK(do_login), client_context);
    
    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 102, 1, 1);

    entryspawn = gtk_button_new_with_label("Login");
    gtk_widget_set_name(entryspawn,"log");
    g_signal_connect(entryspawn, "clicked", G_CALLBACK(do_login), client_context);
    gtk_grid_attach(GTK_GRID(grid), entryspawn, 1, 103, 1, 1);

    labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 104, 1, 1);

    Registration = gtk_button_new_with_label("Sign In");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(make_registration), client_context);
    //g_signal_connect(Registration, "clicked", G_CALLBACK(mx_show_dialog), "hello");
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);



    gtk_widget_set_size_request(GTK_WIDGET(window),1024,768);
    //gtk_window_set_resizable(GTK_WIDGET(window), FALSE);
    gtk_widget_show_all(window);

}
