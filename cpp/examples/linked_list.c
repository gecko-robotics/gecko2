#include <stdlib.h>
// #include <gecko2.hpp>
#include <linked_list.h>


int main() {
  printf("hello\n");

  list_t list;
  list_init(&list);

  // node_t *list = NULL;
  for (int i = 0; i<20; ++i) {
    int* p = (int*)malloc(sizeof(int));
    *p = i;
    list_insert_end(&list, (void*)p);
    printf("%p\n", list.head);
  }

  printf("list size: %d\n", (int)list.size);

  // int i =0;
  // node_t *p = list;
  // while (p != NULL) {
  //   printf("i = %d\n", *(int*)(p->data));
  //   p = p->next;
  // }

  list_free(&list);

  return 0;
}