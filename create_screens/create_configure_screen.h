#ifndef CREATE_CONFIGURE_SCREEN
#define CREATE_CONFIGURE_SCREEN

#include <gtk/gtk.h>
#include <stdlib.h>
#include "../helper/window.h"
#include "../helper/utilities.h"
#include "../helper/universal_variables.h"
#include "../helper/application_state.h"



void
create_configure_screen ();




typedef struct
{
  GtkWidget *grid;
  GtkWidget *inner_stack;

  GtkWidget *check_button_reapeat_cards;

  GtkWidget *check_button_word_simple;
  GtkWidget *check_button_word_complex;
  GtkWidget *check_button_card;

  GtkWidget *number_of_cards;
  GtkWidget *number_of_words;

  GtkWidget *combo_box_order;

  GtkWidget *start_button;
} check_and_shift_data;


#endif // CREATE_CONFIGURE_SCREEN
