#ifndef _ITER_H
#define _ITER_H

#include "list_it.h"

float     iter_get_value      (iterator it);
void      iter_set_value      (iterator* it, float value);
iterator  iter_next           (iterator it);
iterator  iter_prev           (iterator it);
bool      iter_is_equal       (iterator it1, iterator it2);
iterator  iter_begin          (List* l);
iterator  iter_end             (List* l);
iterator  iter_last_elem      (List* l);
void      iter_insert_before  (iterator* it, float value);
void      iter_delete         (iterator* it);

#endif
