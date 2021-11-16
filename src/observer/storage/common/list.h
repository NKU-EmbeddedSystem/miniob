//
// Created by Light-Laptop on 2021/11/15.
//

#ifndef MINIDB_LIST_H
#define MINIDB_LIST_H

typedef struct __list_head {
  struct __list_head *prev;
  struct __list_head *next;
} list_head;

inline void list_init(list_head *list) {
  list->prev = list->next = list;
}

inline void list_add(list_head *pos, list_head *element) {
  list_head *next = pos->next;
  pos->next = next->prev = element;
  element->prev = pos;
  element->next = next;
}

inline void list_add_prev(list_head *pos, list_head *element) {
  list_head *prev = pos->prev;
  prev->next = pos->prev = element;
  element->prev = prev;
  element->next = pos;
}

inline void list_delete(list_head *element) {
  list_head *prev = element->prev;
  list_head *next = element->next;
  prev->next = next;
  next->prev = prev;
  element->prev = element->next = element;
}

inline int list_empty(list_head *list) {
  return (list->next == list) && (list->prev == list);
}

typedef unsigned long ptr_t;

#define member_offset(type, member) ((ptr_t)&(((type *)0)->member))
#define container_of(type, member, ptr) ((type *)(((ptr_t)(ptr)) - member_offset(type, member)))

#endif //MINIDB_LIST_H
