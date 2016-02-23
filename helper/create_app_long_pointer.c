//#include "create_app_long_pointer.h"
//
//
//
//void
//initiate_app_long_pointers ()
//{
//  v_app_long_ptrs = malloc(0);
//  current_size = 0;
//  current_memory = 0;
//}
//
//void *
//create_app_long_pointer (size_t memory)
//{
//  void* new_ptr = malloc(memory);
//
//  current_memory += sizeof(void *);
//
//  void **newMem = (void **)realloc(v_app_long_ptrs, current_memory);
//  if(!newMem)
//  {
//    // handle error
//  }
//
//  v_app_long_ptrs = newMem;
//
//  v_app_long_ptrs[current_size++] = new_ptr;
//  return new_ptr;
//}
//
//void
//delete_app_long_pointers()
//{
//  for(unsigned int i = 0;i < current_size; i++)
//  {
//    free(v_app_long_ptrs[i]);
//  }
//  free(v_app_long_ptrs);
//}
