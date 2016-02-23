#include "utilities.h"


GtkWidget *
create_stack_400 ()
{
  GtkWidget *stack = gtk_stack_new ();
  gtk_stack_set_transition_duration (GTK_STACK (stack), 400);
  gtk_stack_set_transition_type (GTK_STACK (stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
  return stack;
}

char *number_to_wordish(int i)
{
  /* two digits for the ending and 6 for max number length plus  */
  char *c = malloc (sizeof (char) * 8);
  sprintf(c, "%d", i);

  const int k = strlen(c)-1;


  if(k >= 1 && c[k-1] == '1')
    sprintf(c, "%s%s", c, "th");
  else if(c[k] == '1')
    sprintf(c, "%s%s", c, "st");

  else if(c[k] == '2')
    sprintf(c, "%s%s", c, "nd");

  else if(c[k] == '3')
    sprintf(c, "%s%s", c, "rd");

  else /* all other roads lead to rome */
    sprintf(c, "%s%s", c, "th");

  return c;
}
