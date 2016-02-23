#include "create_score_screen.h"




static GtkWidget *text;


void
initialize_score_screen(){
  int total = get_settings()->item_amount;
  int incorrect = get_failures();
  int correct = total-incorrect;
  int precentage_correct = (float)correct/(float)total*100;



  char show_me[256];// give plenty of padding
  sprintf(show_me,
"You got %i out of %i correct.\n\
Thats %i percent correct.", correct, total, precentage_correct);
  gtk_label_set_text (GTK_LABEL(text), show_me);
}



void
create_score_screen (){
  GtkWidget *grid;

  GtkWidget *instruction_label;


  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (grid), 15);

  GtkWidget *frame = gtk_frame_new ("");
  gtk_stack_add_named (GTK_STACK (get_application_stack()), frame, "score_screen");
  gtk_widget_set_halign (frame,GTK_ALIGN_CENTER);
  gtk_widget_set_valign (frame,GTK_ALIGN_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 15);

  gtk_container_add (GTK_CONTAINER (frame), grid);


  const int margin = 5;

  /* create label */
  instruction_label = gtk_label_new ("Your score:");
  gtk_grid_attach (GTK_GRID (grid), instruction_label, 0, 0, 2, 1);


  /*Create a new entry box, and add it to the window*/


  GtkWidget *frame2 = gtk_frame_new ("");
  gtk_widget_set_margin_bottom (frame2, margin);
  gtk_grid_attach (GTK_GRID (grid), frame2, 0, 1, 2, 1);

  text = gtk_label_new ("empty");
//  gtk_widget_set_name (text, "large_text_200");
  gtk_widget_set_margin_bottom (text, margin*3);
  gtk_widget_set_size_request (text, 400 , -1);
  gtk_container_add (GTK_CONTAINER (frame2), text);



  score_screen_info *info = malloc (sizeof (score_screen_info));




  info->current = 0;
  info->instruction_label = instruction_label;
  info->text = text;

//  gtk_widget_show_all (grid);
}
