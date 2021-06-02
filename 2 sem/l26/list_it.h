#ifndef _LIST_IT_H
#define _LIST_IT_H

typedef struct {
    float  value;
    int    prev_index;
    int    next_index;
} list_elem;

typedef struct {
    list_elem*    buffer;
    int           capacity;
    int           size;
    int           first_empty_index;
    int           barrier_elem;
} List;

typedef struct {
    List*  list;
    int    prev;
} iterator;

#endif
