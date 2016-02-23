#include "create_configure_screen.h"

static void
repeat_cards_checked (GtkWidget *button,
                      gpointer   user_data)
{
    check_and_shift_data *data = user_data;
    if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button) ) == FALSE)
    {
      gtk_spin_button_set_range (GTK_SPIN_BUTTON (data->number_of_cards), 1, 52);
    }
    else
    {
      gtk_spin_button_set_range (GTK_SPIN_BUTTON (data->number_of_cards), 1, 999999);
    }
}

static void
button_toggled_simple_words (GtkWidget *button,
                             gpointer   user_data)
{
    if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button) ))
    {
      check_and_shift_data *data = user_data;
      GtkStack *stack = GTK_STACK (data->inner_stack);
      gtk_widget_set_sensitive (data->check_button_word_complex, TRUE);
      gtk_stack_set_visible_child_name (stack, "words");
    }
}

static void
button_toggled_cards (GtkWidget *button,
                      gpointer   user_data)
{
    if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button) ))
    {
      check_and_shift_data *data = user_data;
      GtkStack *stack = GTK_STACK (data->inner_stack);
      gtk_widget_set_sensitive (data->check_button_word_complex, FALSE);
      gtk_stack_set_visible_child_name (stack, "cards");
    }
}

static void
check_and_shift (GtkWidget *widget,
                 gpointer   data)
{
  check_and_shift_data *passed_data = data;
  configuration_settings *settings = get_settings ();

  settings->order = gtk_combo_box_get_active (GTK_COMBO_BOX (passed_data->combo_box_order));



  /* set variable defining the type */
  settings->item_type = ItemTypesNone;
  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (passed_data->check_button_word_simple) ))
  {
    settings->item_type = ItemTypesSimpleWords;
    settings->item_amount = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (passed_data->number_of_words));
  }

  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (passed_data->check_button_word_complex) ))
  {
    settings->item_type = ItemTypesComplexWords;
    settings->item_amount = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (passed_data->number_of_words));
  }

  if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (passed_data->check_button_card) ))
  {
    settings->item_type = ItemTypesCards;
    settings->item_amount = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (passed_data->number_of_cards));
  }

  settings->has_repeats = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (passed_data->check_button_reapeat_cards));

  /* make sure everything required is set */
  if (settings->order == OrderNone && (settings->item_type == ItemTypesSimpleWords ||
                                       settings->item_type == ItemTypesComplexWords))
  {
    create_error_dialog_box ("Please pick the order!");
    printf("Error, no order picked!\n");
  }
  else
  {
    shift_to_study_screen();
  }
}




/* divided for readability purposes*/
inline static void
create_configure_screen_cards (GtkWidget *stack, check_and_shift_data *data)
{
  configuration_settings *conf_settings = get_settings ();
  GtkWidget *grid;

  GtkWidget *label;
  GtkWidget *seperator;


  grid = gtk_grid_new ();

  gtk_stack_add_named (GTK_STACK (stack), grid, "cards");


  const int margin = 5;
  int count = 0;

  /* create label */
  label = gtk_label_new ("Please select the amount of cards to generate:");
  gtk_grid_attach (GTK_GRID (grid), label, 0, count++, 1, 1);

  /* create seperator */
  seperator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_grid_attach (GTK_GRID (grid), seperator, 0, count++, 1, 1);

  /* create spin button */
  data->number_of_cards = gtk_spin_button_new_with_range (1,52,1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (data->number_of_cards), conf_settings->item_amount);
  gtk_grid_attach (GTK_GRID (grid), data->number_of_cards, 0, count++, 1, 1);
  gtk_widget_set_margin_bottom (data->number_of_cards, margin+10);


  /* create a check button */
  data->check_button_reapeat_cards = gtk_check_button_new_with_label ("Allow Repeats?");
  gtk_grid_attach (GTK_GRID (grid), data->check_button_reapeat_cards, 0, count++, 1, 1);
  gtk_widget_set_margin_bottom (data->check_button_reapeat_cards, margin);

  g_signal_connect (GTK_TOGGLE_BUTTON (data->check_button_reapeat_cards), "toggled",
                    G_CALLBACK (repeat_cards_checked), data);


  gtk_widget_show_all(grid);
}





/* divided for readability purposes*/
inline static void
create_configure_screen_words (GtkWidget *stack, check_and_shift_data *data)
{
  configuration_settings *conf_settings = get_settings ();
  GtkWidget *grid;

  GtkWidget *label;
  GtkWidget *seperator;


  grid = gtk_grid_new ();

  gtk_stack_add_named (GTK_STACK (stack), grid, "words");


  const int margin = 5;
  int count = 0;

  /* create label */
  label = gtk_label_new ("Please select the amount of items to generate:");
  gtk_grid_attach (GTK_GRID (grid), label, 0, count++, 1, 1);

  /* create seperator */
  seperator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_grid_attach (GTK_GRID (grid), seperator, 0, count++, 1, 1);

  /* create spin button */
  data->number_of_words = gtk_spin_button_new_with_range (1,999999,1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (data->number_of_words), conf_settings->item_amount);
  gtk_grid_attach (GTK_GRID (grid), data->number_of_words, 0, count++, 1, 1);
  gtk_widget_set_margin_bottom (data->number_of_words, margin+10);




  /* create combo box */
  data->combo_box_order = gtk_combo_box_text_new ();
  const char *order[] = {"Select Order To Recite", "Forwards", "Backwards", "Random"};

  for (unsigned int i = 0; i < G_N_ELEMENTS (order); i++){
    gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (data->combo_box_order), order[i]);
  }
  gtk_combo_box_set_active (GTK_COMBO_BOX (data->combo_box_order), 0);
  gtk_grid_attach (GTK_GRID (grid), data->combo_box_order, 0, count++, 1, 1);
  gtk_widget_set_margin_bottom (data->combo_box_order, margin+10);




  gtk_widget_show_all(grid);
}







void
create_configure_screen (){
  GtkWidget *grid;


  GtkWidget *inner_stack = create_stack_400();

  GtkWidget *label;
  GtkWidget *seperator;

  /* create the configuration data */
  configuration_settings *conf_settings = malloc(sizeof(configuration_settings));
  set_settings (conf_settings);
  conf_settings->item_amount = 15;
  conf_settings->item_type = ItemTypesNone;
  conf_settings->order = OrderNone;



  /* create our settings variable */
  check_and_shift_data *data = malloc(sizeof(check_and_shift_data));
  data->inner_stack = inner_stack;



  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();
  gtk_container_set_border_width (GTK_CONTAINER (grid), 15);
  data->grid = grid;

  GtkWidget *frame = gtk_frame_new ("");
  gtk_stack_add_named (GTK_STACK (get_application_stack()), frame, "configure_screen");
  gtk_widget_set_halign (frame,GTK_ALIGN_CENTER);
  gtk_widget_set_valign (frame,GTK_ALIGN_CENTER);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 15);

  gtk_container_add (GTK_CONTAINER (frame), grid);

  const int margin = 5;
  int count = 0;

  /* create label */
  label = gtk_label_new ("Please select types of items to place into the list:");
  gtk_grid_attach (GTK_GRID (grid), label, 0, count++, 1, 1);

  /* create seperator */
  seperator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_widget_set_margin_bottom (seperator, margin);
  gtk_grid_attach (GTK_GRID (grid), seperator, 0, count++, 1, 1);


  data->check_button_word_simple = gtk_radio_button_new_with_label (NULL, "Simple Words");
  gtk_grid_attach (GTK_GRID (grid), data->check_button_word_simple, 0, count++, 1, 1);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (data->check_button_word_simple), FALSE);
  gtk_widget_set_margin_bottom (data->check_button_word_simple, margin);

  data->check_button_word_complex = gtk_check_button_new_with_label ("Complex Words Too");
  gtk_grid_attach (GTK_GRID (grid), data->check_button_word_complex, 0, count++, 1, 1);
  gtk_widget_set_margin_bottom (data->check_button_word_complex, margin);

  data->check_button_card = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (data->check_button_word_simple), "Cards");
  gtk_grid_attach (GTK_GRID (grid), data->check_button_card, 0, count++, 1, 1);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (data->check_button_card), FALSE);
  gtk_widget_set_margin_bottom (data->check_button_card, margin);

  g_signal_connect (GTK_TOGGLE_BUTTON (data->check_button_word_simple), "toggled",
                    G_CALLBACK (button_toggled_simple_words), data);
  g_signal_connect (GTK_TOGGLE_BUTTON (data->check_button_card), "toggled",
                    G_CALLBACK (button_toggled_cards), data);



  gtk_grid_attach (GTK_GRID (grid), inner_stack, 0, count++, 1, 1);
  gtk_stack_set_vhomogeneous (GTK_STACK (inner_stack), FALSE);

  create_configure_screen_words (inner_stack, data);
  create_configure_screen_cards (inner_stack, data);
  gtk_stack_set_visible_child_name (GTK_STACK (inner_stack), "words");



  /* create button */

  data->start_button = gtk_button_new_with_label ("Start Studying!");
  gtk_grid_attach (GTK_GRID (grid), data->start_button, 0, count++, 1, 1);
  g_signal_connect (data->start_button, "clicked", G_CALLBACK (check_and_shift), data);
  gtk_widget_set_margin_bottom (data->start_button, margin+10);


  gtk_widget_show_all(grid);
}
