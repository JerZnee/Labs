#ifndef INC_8_LIST_H
#define INC_8_LIST_H
#ifndef _UI_LIST_H

#define _UI_LIST_H
#include <stdbool.h>
#include "list_it.h"

void l_create(list *l);
void l_destroy(list *l);
bool l_is_empty(list l);
unsigned int l_get(list l, unsigned long int i);
void l_print(list l);
int l_size(list l);
void l_insert(list *l, unsigned long int i, unsigned long int val);
void l_push_front(list *l, unsigned long int val);
void l_push_back(list *l, unsigned long int val);
void l_remove(list *l, int i);
void l_pop_front(list *l);
void l_pop_back(list *l);
void l_reverse(list *l);

#endif

#endif //INC_8_LIST_H
