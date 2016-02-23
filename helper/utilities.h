#ifndef MYUTILITIES_H
#define MYUTILITIES_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* note, does not attach to anything
it just comes with some default settings*/
GtkWidget *
create_stack_400 ();

char *number_to_wordish(int i);


#endif // MYUTILITIES_H
