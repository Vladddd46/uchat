#include "client.h"

void back_to_menu(GtkWidget *back, client_context_t *client_context){
    gtk_widget_destroy(grid);
    gtk_widget_destroy(back);
    main_menu(client_context->sockfd);
}

void make_registration(GtkWidget *Registration, client_context_t *client_context){
    GtkWidget *back;

    gtk_widget_destroy(grid);


    grid = gtk_grid_new();
    gtk_widget_set_name(grid,"gride");
    gtk_fixed_put(GTK_FIXED (fixed), grid, 350,175);

    GdkPixbuf *iconn = gdk_pixbuf_new_from_file("./media/img/pokeball.png",NULL);
    iconn = gdk_pixbuf_scale_simple(iconn, 128,128, GDK_INTERP_BILINEAR);
    GtkWidget *iconnn = gtk_image_new_from_pixbuf(iconn);
     gtk_widget_set_name(iconnn,"image");
     gtk_grid_attach(GTK_GRID(grid), iconnn, 1, 98, 1, 1);

    login = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(login),"Login");
    gtk_grid_attach(GTK_GRID(grid), login, 1, 99, 1, 1);

    nickname = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(nickname),"Username");
    gtk_grid_attach(GTK_GRID(grid), nickname, 1, 100, 1, 1);

    labell = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell, 1, 101, 1, 1);

    Password = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(Password),"Password");
    gtk_grid_attach(GTK_GRID(grid), Password, 1, 102, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(Password),FALSE);

    SecondPassword = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(SecondPassword),"Confirm your password");
    gtk_grid_attach(GTK_GRID(grid), SecondPassword, 1, 103, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(SecondPassword),FALSE);

    labell2 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell2, 1, 104, 1, 1);


    Registration = gtk_button_new_with_label("Sign Up");
    gtk_widget_set_name(Registration,"reg");
    g_signal_connect(Registration, "clicked", G_CALLBACK(do_registration), client_context);
    gtk_grid_attach(GTK_GRID(grid), Registration, 1, 105, 1, 1);

    labell3 = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), labell3, 1, 106, 1, 1);

    back = gtk_button_new_with_label("Back to Login");
    gtk_widget_set_name(back,"log");
    g_signal_connect(back, "clicked", G_CALLBACK(back_to_menu), client_context);
    gtk_grid_attach(GTK_GRID(grid), back, 1, 107, 1, 1);

    gtk_widget_show_all(window);
}
