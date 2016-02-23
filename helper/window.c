#include "window.h"

static GtkWidget *ptr_to_window;

void
set_window (GtkWidget *win)
{
  ptr_to_window = win;
}

GtkWidget *
get_window ()
{
  return ptr_to_window;
}

static void
create_error_dialog_box_response (GtkDialog *dialog,
                                  gint       response_id,
                                  gpointer   user_data)
{
  gtk_widget_destroy (GTK_WIDGET (dialog));
}

void
create_error_dialog_box (char *str)
{
  GtkWidget *message_dialog = gtk_message_dialog_new (GTK_WINDOW (get_window ()), GTK_DIALOG_MODAL,
    GTK_MESSAGE_ERROR,
    GTK_BUTTONS_OK,
    str);

  g_signal_connect (GTK_DIALOG (message_dialog), "response",
                    G_CALLBACK (create_error_dialog_box_response), NULL);

  gtk_widget_show_all (message_dialog);
}
