#ifndef CREATE_SCORE_SCREEN
#define CREATE_SCORE_SCREEN

#include <gtk/gtk.h>
#include <stdlib.h>
#include "../helper/window.h"
#include "../helper/utilities.h"
#include "../helper/universal_variables.h"
#include "../helper/application_state.h"

void
initialize_score_screen();

void
create_score_screen ();

typedef struct
{
  unsigned int current;
  GtkWidget *instruction_label;
  GtkWidget *text;
} score_screen_info;


#endif // CREATE_SCORE_SCREEN
