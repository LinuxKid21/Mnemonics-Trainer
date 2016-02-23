#include "universal_variables.h"

// 'U' for universal
static configuration_settings *Usettings;

static char **Uitems = NULL;
static unsigned int Uitem_count;
static GtkWidget *Uprogress_bar;
static int Ufailures = 0;
static int Usemi_failures = 0;



void
set_progress_bar (GtkWidget *bar)
{
  Uprogress_bar = bar;
}

void
set_progress (double prog)
{
   gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (Uprogress_bar), prog);
}

void
set_progress_hidden ()
{
  gtk_widget_hide(Uprogress_bar);
}

void
set_progress_visible ()
{
  gtk_widget_show(Uprogress_bar);
}



void
set_settings (configuration_settings *set)
{
  Usettings = set;
}

configuration_settings *
get_settings ()
{
  return Usettings;
}


void
add_semi_failure ()
{
  Usemi_failures++;
}

void
add_failure ()
{
  Ufailures++;
  Usemi_failures--;
}

int
get_semi_failures ()
{
  return Usemi_failures;
}

int
get_failures ()
{
  return Ufailures;
}

void
clear_failures () {
  Ufailures = 0;
  Usemi_failures = 0;
}


void
set_items (char **items, unsigned int item_count)
{
  Uitems = items;
  Uitem_count = item_count;
}

char **
get_items ()
{
  return Uitems;
}


unsigned int
get_item_count ()
{
  return Uitem_count;
}
