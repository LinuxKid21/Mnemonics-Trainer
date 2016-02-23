#ifndef GENERATE_ITEMS_H
#define GENERATE_ITEMS_H
#include "../create_screens/create_configure_screen.h"
#include <time.h>
#include <stdlib.h>



/* generate_items_words works with files where there is one word per line. */
void
generate_items_words (char *file_name, const int file_length, gboolean remove_doubles);


#endif // GENERATE_ITEMS_H
