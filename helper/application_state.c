#include "application_state.h"

static GtkWidget *ptr_to_stack;

void
setup_application_state () {
  GtkWidget *box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);;
  gtk_container_add (GTK_CONTAINER (get_window()), box);


  ptr_to_stack = create_stack_400 ();
  gtk_stack_set_homogeneous (GTK_STACK (ptr_to_stack), FALSE);
  gtk_box_pack_start (GTK_BOX (box), ptr_to_stack, TRUE, TRUE, 0);


  GtkWidget *progress_bar = gtk_progress_bar_new ();

  gtk_box_pack_start (GTK_BOX (box), progress_bar, FALSE, FALSE, 0);
  set_progress_bar (progress_bar);
  set_progress_hidden ();




  create_configure_screen ();
  create_study_screen ();
  create_quiz_screen ();
  create_score_screen ();
}


void
add_screen_onto_gtk_stack(GtkWidget *child, const char *name) {
  gtk_stack_add_named (GTK_STACK (ptr_to_stack), child, name);
}


void
shift_to_config_screen () {

  gtk_stack_set_visible_child_name (GTK_STACK (ptr_to_stack),
                                    "configure_screen");

  set_progress_hidden ();
  set_progress (0);
}


void
shift_to_study_screen ()
{
  configuration_settings *settings = get_settings ();

  if(settings->item_type == ItemTypesComplexWords)
    generate_items_words("./dictionary.txt", 25189/* file length */, TRUE);
  if(settings->item_type == ItemTypesSimpleWords)
    generate_items_words("./dictionary_small.txt", 846/* file length */, TRUE);
  if(settings->item_type == ItemTypesCards)
    generate_items_words("./cards.txt", 52/* file length */, settings->has_repeats);


  gtk_stack_set_visible_child_name (GTK_STACK (ptr_to_stack),
                                    "study_screen");

  set_progress_visible ();
  set_progress (0);

  initialize_study_screen();
}



void
shift_to_quiz_screen ()
{
  set_progress (0);
  gtk_stack_set_visible_child_name (GTK_STACK (ptr_to_stack),
                                    "quiz_screen");
  initialize_quiz_screen ();
}


void
shift_to_score_screen ()
{
  initialize_score_screen ();
  set_progress (0);
  set_progress_hidden ();
  gtk_stack_set_visible_child_name (GTK_STACK (ptr_to_stack),
                                    "score_screen");
}
