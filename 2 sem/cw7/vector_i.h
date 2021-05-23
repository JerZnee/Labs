#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdbool.h>

typedef struct {
    int size;
    int capacity;
    double* buffer;
} vector;

void    v_create(vector* v);
void    v_destroy(vector* v);
bool    v_resize(vector* v, int new_size);
int     v_size(vector* v);
int     v_get(vector* v, int position);
bool    v_append(vector* v, int value);
void    v_clear(vector* v);
void    v_set(vector* v, int position, int value);
void    v_insert(vector* v, int position, int value);

#endif