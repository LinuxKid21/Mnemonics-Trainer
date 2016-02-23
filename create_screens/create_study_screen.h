#ifndef CREATE_STUDY_SCREEN
#define CREATE_STUDY_SCREEN

#include <gtk/gtk.h>
#include <stdlib.h>
#include "../helper/window.h"
#include "../helper/utilities.h"
#include "../helper/universal_variables.h"
#include "../helper/application_state.h"



void
create_study_screen ();

void initialize_study_screen ();

typedef struct
{
  int current;
  GtkWidget *instruction_label;
  GtkWidget *text;
  GtkWidget *previous_button;
  GtkWidget *next_button;
} study_screen_info;

#endif // CREATE_STUDY_SCREEN
