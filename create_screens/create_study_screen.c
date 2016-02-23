#include "create_study_screen.h"

// currently being uneccesarily passed around
static study_screen_info *info;


static void
update_text (study_screen_info *info)
{
  set_progress ((double)info->current / (double)get_item_count ());

  char *print_me = malloc (sizeof (char) * 25);
  char *wordish = number_to_wordish(info->current);
  char **items;

  items = get_items ();


  sprintf(print_me, "%s%s%s", "The ", wordish, " item is:");
  gtk_label_set_text (GTK_LABEL (info->instruction_label), print_me);

  gtk_label_set_text (GTK_LABEL (info->text), items[info->current-1]);
  free (print_me);
  free (wordish);
}


static void
on_next (GtkButton *entry,
         gpointer  user_data)
{
  study_screen_info *info = user_data;
  info->current++;
  if(info->current == get_item_count ())
  {
    gtk_button_set_label(GTK_BUTTON (info->next_button), "To Quiz");
    update_text(info);
  }
  else if(info->current == get_item_count ()+1)
  {
    //! do not update text or we will have an overflow!
    shift_to_quiz_screen();
  }
  else
  {
    update_text(info);
  }
}

static void
on_previous (GtkButton *entry,
             gpointer  user_data)
{
  if(info->current == get_item_count ())
    gtk_button_set_label(GTK_BUTTON (info->next_button), "Next");
  info->current--;
  if(info->current < 1)
  {
    info->current = 0;
    gtk_label_set_text (GTK_LABEL (info->instruction_label), "click next to begin");
    gtk_label_set_text (GTK_LABEL (info->text), "");
    set_progress (0);
  }
  else
  {
    update_text(info);
  }
}





void
create_study_screen (){
  GtkWidget *grid;

  GtkWidget *instruction_label;
  GtkWidget *text;


  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (grid), 15);

  GtkWidget *frame = gtk_frame_new ("");
  add_screen_onto_gtk_stack(frame, "study_screen");
  gtk_widget_set_halign (frame,GTK_ALIGN_CENTER);
  gtk_widget_set_valign (frame,GTK_ALIGN_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 15);

  gtk_container_add (GTK_CONTAINER (frame), grid);


  const int margin = 5;

  /* create label */
  instruction_label = gtk_label_new ("click next to begin");
  gtk_grid_attach (GTK_GRID (grid), instruction_label, 0, 0, 2, 1);


  /*Create a new entry box, and add it to the window*/


  GtkWidget *frame2 = gtk_frame_new ("");
  gtk_widget_set_margin_bottom (frame2, margin);
  gtk_grid_attach (GTK_GRID (grid), frame2, 0, 1, 2, 1);

  text = gtk_label_new ("");
  gtk_widget_set_name (text, "large_text_200");
  gtk_widget_set_margin_bottom (text, margin*3);
  gtk_widget_set_size_request (text, 400 , -1);
  gtk_container_add (GTK_CONTAINER (frame2), text);



  info = malloc (sizeof (study_screen_info));


  /* create button */

  GtkWidget *button1;
  button1 = gtk_button_new_with_label ("Previous");
  gtk_grid_attach (GTK_GRID (grid), button1, 0, 2, 1, 1);

  g_signal_connect (GTK_BUTTON (button1), "clicked",
                    G_CALLBACK (on_previous), NULL);

  GtkWidget *button2;
  button2 = gtk_button_new_with_label ("Next");
  gtk_grid_attach (GTK_GRID (grid), button2, 1, 2, 1, 1);

  g_signal_connect (GTK_BUTTON (button2), "clicked",
                    G_CALLBACK (on_next), info);



  info->current = 0;
  info->instruction_label = instruction_label;
  info->text = text;
  info->previous_button = button1;
  info->next_button = button2;

//  gtk_widget_show_all (grid);
}

void
initialize_study_screen() {
  info->current = 0;
  on_previous(NULL, NULL);
  gtk_button_set_label(GTK_BUTTON (info->next_button), "Next");
}
