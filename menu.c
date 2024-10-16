#include <gtk/gtk.h>

//Método para regresar a la ventana principal (Menú)
static void regresarMenu(GtkWidget *button, gpointer data) {
    GtkWidget *main_window = GTK_WIDGET(data);
    
    //Mostrar la ventana principal
    if (GTK_IS_WIDGET(main_window)) {
        gtk_widget_show(main_window);
    }
    
    //Destruir ventana anterior
    GtkWidget *new_window = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(new_window);
}

//Muestra la ventana de instrucciones del juego
static void instruccionesJuegoVentana(GtkWidget *widget, gpointer data) {
    GtkWidget *new_window;
    GtkWidget *main_window = GTK_WIDGET(data);

    //Crear ventana nueva
    new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //Título de la ventana
    gtk_window_set_title(GTK_WINDOW(new_window), "Instrucciones");
    //Tamaño de la ventana
    gtk_window_set_default_size(GTK_WINDOW(new_window), 1600, 900);
    //Posición de la ventana
    gtk_window_set_position(GTK_WINDOW(new_window), GTK_WIN_POS_CENTER);
    //Borde
    gtk_container_set_border_width(GTK_CONTAINER(new_window), 10);

    //Destruye la ventana
    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    //Ocultar la ventana principal
    if (GTK_IS_WIDGET(main_window)) {
        gtk_widget_hide(main_window);
    }

    //Crear nueva ventana
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(new_window), grid);
    
     //Botón Regresar
    GtkWidget *button_back = gtk_button_new_with_label("Regresar");
    //Regresa al menu principal
    g_signal_connect(button_back, "clicked", G_CALLBACK(regresarMenu), main_window);
    gtk_grid_attach(GTK_GRID(grid), button_back, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 0, 1, 2, 1);

    //Crear label con texto para las instrucciones del juego
    GtkWidget *label_instructions = gtk_label_new("Instrucciones:\n\nLa barra se mueve con la tecla w y s. Se debe evitar que la pelota salga de la pantalla\n"
                                                  "Si la pelota sale de la pantalla, la puntuación aumenta en uno. El juego termina cuando alguno de los jugadores consiga cinco puntos.");
    //Texto a la izquierda
    gtk_label_set_justify(GTK_LABEL(label_instructions), GTK_JUSTIFY_LEFT);
    //Posicion del lable
    gtk_grid_attach(GTK_GRID(grid), label_instructions, 0, 3, 10, 10);


    //Mostrar la nueva ventana
    gtk_widget_show_all(new_window);
}

//Muestra la ventana de instrucciones del juego
static void inicioJuegoVentana(GtkWidget *widget, gpointer data) {
    GtkWidget *new_window;
    GtkWidget *main_window = GTK_WIDGET(data);

    // Crear nueva ventana
    new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //Título de la ventana
    gtk_window_set_title(GTK_WINDOW(new_window), "PONG");
    //Tamaño de la ventana
    gtk_window_set_default_size(GTK_WINDOW(new_window), 1600, 900);
    //Posición de la ventana
    gtk_window_set_position(GTK_WINDOW(new_window), GTK_WIN_POS_CENTER);
    //No se puede cambiar el tamaño de la ventana
    gtk_window_set_resizable(GTK_WINDOW(new_window), FALSE);
    //Borde
    gtk_container_set_border_width(GTK_CONTAINER(new_window), 10);

    //Destruye la ventana
    g_signal_connect(new_window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    //Ocultar la ventana principal
    if (GTK_IS_WIDGET(main_window)) {
        gtk_widget_hide(main_window);
    }

    //Crear nueva ventana
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(new_window), grid);

    //Botón Regresar
    GtkWidget *button_back = gtk_button_new_with_label("Regresar");
    ////Regresa al menu principal
    g_signal_connect(button_back, "clicked", G_CALLBACK(regresarMenu), main_window);
    gtk_grid_attach(GTK_GRID(grid), button_back, 0, 0, 1, 1);

    //Mostrar la nueva ventana
    gtk_widget_show_all(new_window);
}

//Carga estilo en css
static void cargarEstilo(GtkWidget *widget) {
     GtkCssProvider *cssProvider = gtk_css_provider_new();
    GError *error = NULL;

    // Cargar el CSS desde un archivo
    if (gtk_css_provider_load_from_path(cssProvider, "style.css", &error) == FALSE) {
        g_printerr("Error cargando CSS: %s\n", error->message);
        g_error_free(error);
    }

    // Aplicar el CSS a la ventana actual
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                               GTK_STYLE_PROVIDER(cssProvider),
                                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    g_object_unref(cssProvider);
}


static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *image;


    //Ventana principal
    window = gtk_application_window_new(app);
    //Título de la ventana
    gtk_window_set_title(GTK_WINDOW(window), "PONG");
    //Tamaño de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 1600, 900);
    //Posición de la ventana
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    //No se puede cambiar el tamaño de
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    //Borde
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	//Cargar estilo CSS
    cargarEstilo(window);
    
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    //Espaciado entre filas y columnas
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 250);

    //Espacios en blanco en la parte superior
    for (int i = 0; i < 9; i++) {
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new(""), 0, i, 2, 1);
    }

    //Botón inicio
    button = gtk_button_new_with_label("Inicio");
    //Cuando se da click, el botón lleva a la ventana de inicio de juego
    g_signal_connect(button, "clicked", G_CALLBACK(inicioJuegoVentana), window);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 10, 1, 1);

    //Botón Cómo Jugar?
    button = gtk_button_new_with_label("Cómo Jugar?");
    //Cuando se da click, el botón lleva a la ventana de instrucciones de juego
    g_signal_connect(button, "clicked", G_CALLBACK(instruccionesJuegoVentana), window);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 11, 1, 1);

    //Botón Salir
    button = gtk_button_new_with_label("Salir");
    //Cuando se da click, el botón destruye la ventana y sale completamente del programa
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 12, 1, 1);

    // Crear y añadir la imagen
    image = gtk_image_new_from_file("img/title1.png"); // Cambia esto a la ruta de tu imagen
    gtk_grid_attach(GTK_GRID(grid), image, 2, 0, 1, 13); 


    gtk_widget_show_all(window);
}

int menu(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
