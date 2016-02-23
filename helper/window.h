#ifndef WINDOW_H
#define WINDOW_H

#include <gtk/gtk.h>


void
set_window (GtkWidget *win);

GtkWidget *get_window ();

void
create_error_dialog_box (char *str);




#endif // WINDOW_H
