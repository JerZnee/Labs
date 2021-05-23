#ifndef INC_8_LIST_IT_H
#define INC_8_LIST_IT_H
#ifndef _LIST_ITER_H

#define _LIST_ITER_H
typedef struct{
    unsigned long int val;
    int prev_idx;
    int next_idx;
} list_el;

typedef struct{
    list_el* buf;
    int cap;
    int top_empty_idx;
    int size;
} list;

typedef struct{
    list *list;
    int prev;
} iter;

#endif
#endif //INC_8_LIST_IT_H
