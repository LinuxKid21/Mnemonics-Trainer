#ifndef UNIVERSAL_VARIABLES_H
#define UNIVERSAL_VARIABLES_H
#include <gtk/gtk.h>

int *Uorder_of_items;

enum ItemTypes {
  ItemTypesNone = 0x00,
  ItemTypesNumbers = 0x01,
  ItemTypesSimpleWords = 0x02,
  ItemTypesComplexWords = 0x04,
  ItemTypesCards = 0x08,
  ItemTypesXXX = 0x10,
  ItemTypesYYY = 0x20,
};
enum Order {
  OrderNone = 0,
  OrderForwards = 1,
  OrderBackwards,
  OrderRandom
};


typedef struct
{
  char item_type;
  unsigned int item_amount;
  gboolean has_repeats;
  char order;
} configuration_settings;



void
add_semi_failure ();

void
add_failure ();

int
get_semi_failures ();

int
get_failures ();

void
clear_failures ();


void
set_progress_bar (GtkWidget *bar);

void
set_progress (double prog);

void
set_progress_hidden ();

void
set_progress_visible ();

void
set_settings (configuration_settings *set);

configuration_settings *
get_settings ();


void
set_items (char **items, unsigned int item_count);

char **
get_items ();


int
get_item_count ();

#endif // UNIVERSAL_VARIABLES_H
