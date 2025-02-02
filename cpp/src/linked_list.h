
#pragma once
#include <stdio.h>
#include <stdlib.h>

#if defined __cplusplus
extern "C" {
#endif


typedef struct ListNode {
  void* data;
  struct ListNode *next;
} node_t;

typedef struct LinkedList {
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;

node_t* node_create(void* data) {
  node_t *p = (node_t*)malloc(sizeof(node_t));
  p->data = data;
  p->next = NULL;
  return p;
}

void list_init(list_t *list) {
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void list_insert_end(list_t* list, void* data) {
  // printf("insert start\n");
  node_t *node = node_create(data);

  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
    list->size = 0;
  }
  else {
    list->tail->next = node;
    list->tail = node;
  }
  
  list->size += 1;
  // printf("insert: %d\n", (int)list->size);
}

void list_free(list_t *list) {
  // printf("start\n");
  node_t *p = NULL;
  int i = 0;
  while (list->head != NULL) {
    // printf("loop\n");
    p = list->head;
    list->head = list->head->next;
    // printf("%d: %p %p\n", *(int*)p->data, p, list->head);
    free(p->data);
    free(p);
  }
}


#if defined __cplusplus
}
#endif