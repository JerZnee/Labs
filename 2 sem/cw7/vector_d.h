#ifndef _VECTOR_d_H
#define _VECTOR_d_H

#include <stdbool.h>

typedef struct {
    int size;
    int capacity;
    double* buffer;
} vector_d;

void    d_create(vector_d* v);
void    d_destroy(vector_d* v);
bool    d_resize(vector_d* v, int new_size);
int     d_size(vector_d* v);
double  d_get(vector_d* v, int position);
bool    d_append(vector_d* v, double value);
void    d_clear(vector_d* v);
void    d_set(vector_d* v, int position, double value);
void    d_insert(vector_d* v, int position, double value);

#endif