#include "set_up_toolbar.h"


static void
quit_callback (GSimpleAction *simple,
               GVariant      *parameter,
               gpointer       user_data)
{
  GApplication *application = user_data;

  g_application_quit (application);
}


static void
about_call_back (GSimpleAction *simple,
               GVariant      *parameter,
               gpointer       user_data)
{
  const gchar *auth[] = { "Levi Stoddard <linuxkid21@gmail.com>", NULL };
  GdkPixbuf *logo = gdk_pixbuf_new_from_file("logo.xpm", NULL);
  gtk_show_about_dialog( GTK_WINDOW( get_window() ),
                          "program-name", "Mnuemonics Trainer",
                          "version", "Version 1.0",
                          "comments",
"Mnemonics Trainer is intended as a practicing tool for visual mnemonics.\
 You associate the meaning of a word with an image and associate each\
 Image with each other. It can make a good party trick if you can reconstruct\
 a deck of cards after just shuffling through them once, or reciting a list after only hearing it once.",
                          "authors", auth,
                          "logo", logo,
                          NULL );
}


static void
restart_call_back (GSimpleAction *simple,
                   GVariant      *parameter,
                   gpointer       user_data)
{
  shift_to_config_screen();
}


void
set_up_toolbar (GtkApplication *app)
{
  GSimpleAction *quit_action;
  GSimpleAction *about_action;
  GSimpleAction *restart_action;

  quit_action = g_simple_action_new ("quit", NULL);
  g_signal_connect (quit_action, "activate", G_CALLBACK (quit_callback), app);
  /* It is added to the overall application */
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (quit_action));



  about_action = g_simple_action_new ("about", NULL);
  g_signal_connect (about_action, "activate", G_CALLBACK (about_call_back), app);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (about_action));



  restart_action = g_simple_action_new ("restart", NULL);
  g_signal_connect (restart_action, "activate", G_CALLBACK (restart_call_back), app);
  g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (restart_action));


  GtkBuilder *builder;
  GError *error = NULL;

  builder = gtk_builder_new ();

  gtk_builder_add_from_file (builder, "menubar.ui", &error);
  if (error != NULL) {
     g_print ("%s\n", error->message);
     g_error_free (error);
  }

  GObject *menubar = gtk_builder_get_object (builder, "menubar");
  gtk_application_set_menubar (GTK_APPLICATION (app), G_MENU_MODEL (menubar));

}
