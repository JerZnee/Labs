#ifndef _LIST_H
#define _LIST_H
#include <stdbool.h>
#include "list_it.h"

void     list_create        (List* l);
void     list_destroy       (List* l);
bool     list_is_empty      (List* l);
float    list_get           (List* l, int index);
void     list_print         (List* l);
int      list_size          (List* l);
void     list_insert        (List* l, int index, float value);
void     list_push_front    (List* l, float value);
void     list_push_back     (List* l, float value);
void     list_pop_front     (List* l);
void     list_pop_back      (List* l);
void     list_delete        (List* l, int index);
bool     list_sorted        (List* l);

#endif