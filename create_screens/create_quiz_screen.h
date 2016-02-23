#ifndef CREATE_QUIZ_SCREEN
#define CREATE_QUIZ_SCREEN

#include <gtk/gtk.h>
#include <stdlib.h>
#include "../helper/window.h"
#include "../helper/utilities.h"
#include "../helper/universal_variables.h"
#include "../helper/application_state.h"



void
create_quiz_screen ();

void initialize_quiz_screen ();

typedef struct
{
  unsigned int current;
  GtkWidget *instruction_label;
  GtkWidget *entry_box;
  GtkWidget *previous_button;
  GtkWidget *next_button;
} quiz_screen_info;

#endif // CREATE_QUIZ_SCREEN
