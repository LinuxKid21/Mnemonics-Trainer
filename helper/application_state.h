#ifndef APPLICATION_STATE_H
#define APPLICATION_STATE_H

#include <gtk/gtk.h>
#include "utilities.h"
#include "universal_variables.h"
#include "generate_items.h"
#include "../create_screens/create_configure_screen.h"
#include "../create_screens/create_study_screen.h"
#include "../create_screens/create_quiz_screen.h"
#include "../create_screens/create_score_screen.h"

void
setup_application_state (GtkWidget *window);

GtkWidget *
get_application_stack();

void
shift_to_config_screen ();

void
shift_to_study_screen ();

void
shift_to_quiz_screen ();

void
shift_to_score_screen ();

#endif
