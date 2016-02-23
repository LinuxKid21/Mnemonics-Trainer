#include "generate_items.h"

static int *order_of_items = NULL;


static void
generate_order ()
{
  configuration_settings *settings = get_settings ();
  // free order_of_items if its not null
  if(order_of_items != NULL) {
    // memory leak still!
  }
  order_of_items = malloc (sizeof (int) * settings->item_amount);
  if (settings->order == OrderBackwards && (settings->item_type == ItemTypesSimpleWords || settings->item_type == ItemTypesComplexWords) )
  {
    for(unsigned int i = 0;i < settings->item_amount; i++)
    {
      order_of_items[i] = settings->item_amount - i - 1;
    }
  }
  else
  {
    for(unsigned int i = 0;i < settings->item_amount; i++)
    {
      order_of_items[i] = i;
    }
    if (settings->order == OrderRandom && (settings->item_type == ItemTypesSimpleWords || settings->item_type == ItemTypesComplexWords) )
    {
      for(unsigned int i = 0;i < settings->item_amount*5; i++)
      {
        unsigned int x = ((double)rand()/(double)RAND_MAX)*(double)settings->item_amount;
        unsigned int y = ((double)rand()/(double)RAND_MAX)*(double)settings->item_amount;

        unsigned int temp = order_of_items[x];
        order_of_items[x] = order_of_items[y];
        order_of_items[y] = temp;
      }
    }
  }
  Uorder_of_items = order_of_items;
}

static gboolean check_for_doubles_words (int *random_list, int random_list_size, int possibilities_size)
{
  for (unsigned int i = 0;i < random_list_size; i++)
    for (unsigned int j = 0;j < random_list_size; j++)
      if (i != j && random_list[i] == random_list[j])
      {
        random_list[i] = ((double)rand()/(double)RAND_MAX)*(double)possibilities_size;
        return TRUE;
      }
    return FALSE;
}

static void scramble_words_list (char **random_list, int size)
{
  for(unsigned int i = 0;i < size*15; i++)
  {
    unsigned int x = ((double)rand()/(double)RAND_MAX)*(double)size;
    unsigned int y = ((double)rand()/(double)RAND_MAX)*(double)size;

    char *temp     = random_list[x];
    random_list[x] = random_list[y];
    random_list[y] = temp;
  }
}


void
generate_items_words (unsigned int random_list_size, char *file_name, const int file_length, gboolean remove_doubles)
{
  // erase if items is not empty
  char **items = get_items();
  if(items != NULL) {
    for(int i = 0;i < get_item_count(); i++) {
      free(items[i]);
    }
    free(items);
  }
  items = malloc (random_list_size*sizeof (char *));
  const int largest_word_size = 25;


  srand(time(NULL));

  char word[largest_word_size];

  int random_list[random_list_size];
  for(int i = 0;i < random_list_size; i++)
  {
    random_list[i] = ((double)rand()/(double)RAND_MAX)*(double)file_length;
  }

  if (remove_doubles == TRUE)
  while (check_for_doubles_words (random_list, random_list_size, file_length) == TRUE) {}

  int x = 0;
  int j = 0;
  FILE *file = fopen(file_name, "r");
  while(fgets(word, 25, file) != NULL)
  {
    word[strlen(word)-1] = '\0'; // trucate new line
    for(int i = 0;i < random_list_size; i++)
    {
      if(random_list[i] == j)
      {
        items[x] = malloc (sizeof (char) * largest_word_size);
        strcpy(items[x++], word);
//        printf("%i: %s\n",x,  items[x-1] );
      }
    }
    j++;
  }


  scramble_words_list (items,random_list_size);
  set_items(items, random_list_size);

  fclose(file);

  generate_order ();
}
