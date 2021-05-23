#ifndef INC_8_ITER_H
#define INC_8_ITER_H
#ifndef _UI_ITER_H

#define _UI_ITER_H
#include <stdbool.h>
#include "list_it.h"

unsigned long int iter_get_val(iter it);
void iter_set_val(iter* it, unsigned long int val);
iter iter_next(iter it);
iter iter_prev(iter it);
bool iter_equal(iter it1, iter it2);
iter iter_begin(list *l);
iter iter_last_element(list *l);
iter iter_end(list *l);
void iter_insert_before(iter *it, unsigned long int val);
void iter_remove(iter *it);

#endif
#endif //INC_8_ITER_H
