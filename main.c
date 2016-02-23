#include <gtk/gtk.h>

#include "./helper/set_up_toolbar.h"
#include "./helper/window.h"
#include "./helper/application_state.h"










static void
startup (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;

/*-- CSS ------------------*/
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;
/*---------------------------*/

  set_up_toolbar (app);

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Mnuemonics Trainer");
  gtk_window_set_default_size (GTK_WINDOW (window), 900,500);

  //! this puts window in a global variable
  //! so we don't have to throw it around everywhere.
  set_window(window);

  /* Must be called after set_window is called.
     Sets up a gtk_stack and pushes the configure,
     memorizer, quizer, and score screens onto it. */
  setup_application_state ();






/*---------------- CSS ----------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gsize bytes_written, bytes_read;

  const gchar* home = "./style.css";

  GError *error = 0;

  gtk_css_provider_load_from_path (provider,
                                      g_filename_to_utf8(home, strlen(home), &bytes_read, &bytes_written, &error),
                                      NULL);
  g_object_unref (provider);
/*---------------- CSS ----------------------------------------------------------------------------------------------------*/


  gtk_widget_show_all (window);


  /* initializes certain variables. it is not
     placed inside setup_application_state
     because it sets a widget invisible which
     would only be undone by gtk_widget_show_all */
  shift_to_config_screen();
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{

}


int
main (int    argc,
      char **argv)
{

  GtkApplication *app;
  int status;

  app = gtk_application_new ("com.gmail.linuxkid21.mnuemonics_trainer", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "startup", G_CALLBACK (startup), NULL);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);


  return status;
}
