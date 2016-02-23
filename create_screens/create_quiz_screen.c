#include "create_quiz_screen.h"




static gboolean has_alread_errored;
static gboolean last_was_correct;
static gboolean first_run;
//static int *order_of_items;
static quiz_screen_info *info;


static void
update_text ()
{
  set_progress ((double)info->current / (double)get_item_count ());

  char *print_me = malloc (sizeof (char) * 25);
  char *wordish = number_to_wordish(Uorder_of_items[info->current]+1);


  sprintf(print_me, "%s%s%s", "What is the ", wordish, " item?");
  gtk_label_set_text (GTK_LABEL (info->instruction_label), print_me);


  free (print_me);
  free (wordish);
}



static void
set_default_style ()
{
  gtk_widget_set_name (info->entry_box, "");
  gtk_button_set_label (GTK_BUTTON (info->next_button), "Check");
}
static void
set_error_style ()
{
  gtk_widget_set_name (info->entry_box, "error");
}
static void
set_correct_style ()
{
  gtk_widget_set_name (info->entry_box, "correct");
  gtk_button_set_label (GTK_BUTTON (info->next_button), "Next");
}

static void
on_give_up (GtkWidget *DontUseMe,
            gpointer  user_data)
{
  char **items = get_items ();
  if(!last_was_correct && info->current != get_item_count ()) {
    has_alread_errored = FALSE;
    last_was_correct = TRUE;

    add_failure ();
    set_correct_style (info);
    gtk_entry_set_text (GTK_ENTRY (info->entry_box), items[Uorder_of_items[info->current]]);
  }
}



static void
on_next (GtkWidget *DontUseMe,
         gpointer  user_data)
{
  char **items = get_items ();

  const char *user_item = gtk_entry_get_text (GTK_ENTRY (info->entry_box));


  if (last_was_correct == TRUE)
  {
    last_was_correct = FALSE;
    info->current++;
    gtk_entry_set_text (GTK_ENTRY (info->entry_box), "");
    update_text (info);
    set_default_style (info);


    if(info->current == get_item_count ())
    {
      gtk_label_set_text (GTK_LABEL (info->instruction_label),
                          "Time to see how well you did!");
      gtk_button_set_label (GTK_BUTTON (info->next_button), "Let\'s See!");
    }

    return;
  }

  if(info->current == get_item_count ())
  {
    /* do not update text lest
       we will have an overflow! */
    shift_to_score_screen();
    return;
  }




  if (strcmp (items[Uorder_of_items[info->current]],user_item) == 0)
  {
    if (last_was_correct == FALSE)
    {
      last_was_correct = TRUE;
      set_correct_style (info);
    }
  }
  else
  {
    if (has_alread_errored == FALSE)
    {
      has_alread_errored = TRUE;
      set_error_style (info);
      add_semi_failure ();
    }
    else
    {
      on_give_up (NULL, info);
    }
  }



}





void
create_quiz_screen (){
  has_alread_errored = FALSE;
  last_was_correct = FALSE;
  first_run = TRUE;


  GtkWidget *grid;

  GtkWidget *instruction_label;
  GtkWidget *entry_box;


  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  gtk_grid_set_column_homogeneous (GTK_GRID (grid), TRUE);
  gtk_container_set_border_width (GTK_CONTAINER (grid), 15);

  GtkWidget *frame = gtk_frame_new ("");
  gtk_stack_add_named (GTK_STACK (get_application_stack()), frame, "quiz_screen");
  gtk_widget_set_halign (frame,GTK_ALIGN_CENTER);
  gtk_widget_set_valign (frame,GTK_ALIGN_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 15);

  gtk_container_add (GTK_CONTAINER (frame), grid);


  const int margin = 5;

  /* create label */
  instruction_label = gtk_label_new ("");
  gtk_grid_attach (GTK_GRID (grid), instruction_label, 0, 0, 2, 1);


  info = malloc (sizeof (quiz_screen_info));

  /* create entry box */
  entry_box = gtk_entry_new ();
  gtk_widget_set_name (entry_box, "");
  gtk_widget_set_margin_bottom (entry_box, margin);
  gtk_widget_set_size_request (entry_box, 400 , -1);
  gtk_grid_attach (GTK_GRID (grid), entry_box, 0, 1, 2, 1);

  g_signal_connect (GTK_ENTRY (entry_box), "activate",
                    G_CALLBACK (on_next), info);



  /* create button */

  GtkWidget *button1;
  button1 = gtk_button_new_with_label ("Give Up");
  gtk_grid_attach (GTK_GRID (grid), button1, 0, 2, 1, 1);

  g_signal_connect (GTK_BUTTON (button1), "clicked",
                    G_CALLBACK (on_give_up), info);

  GtkWidget *button2;
  button2 = gtk_button_new_with_label ("Check");
  gtk_grid_attach (GTK_GRID (grid), button2, 1, 2, 1, 1);

  g_signal_connect (GTK_BUTTON (button2), "clicked",
                    G_CALLBACK (on_next), info);



  info->current = 0;
  info->instruction_label = instruction_label;
  info->entry_box = entry_box;
  info->previous_button = button1;
  info->next_button = button2;
}

void initialize_quiz_screen ()
{
  info->current = 0;
  clear_failures();
  set_default_style();
  update_text(info);
}
