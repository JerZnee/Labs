#include <stdlib.h>
#include <stdbool.h>
#include "vector_d.h"

void d_create(vector_d* v){
    v->size     = 0;
    v->capacity = 0;
    v->buffer   = NULL;
}

void d_destroy(vector_d* v){
    v->size     = 0;
    v->capacity = 0;
    free(v->buffer);
    v->buffer   = NULL;
}

int d_size(vector_d* v){
    return v->size;
}

double d_get(vector_d* v, int position){
    return v->buffer[position];
}

void d_set(vector_d* v, int position, double value){
    v->buffer[position] = value;
}

bool d_grow_buffer(vector_d* v){
    int new_capacity = v->capacity * 3 / 2;
    if (v->capacity == 0){
        new_capacity = 10;
    }

    double* tmp = realloc(v->buffer, sizeof(double) * new_capacity);
    if (tmp != NULL){
        v->buffer = tmp;
        v->capacity = new_capacity;
        return true;
    } else {
        return false;
    }
}

bool d_append(vector_d* v, double value){
    if (v->size >= v->capacity){
        if (!d_grow_buffer(v)){
            return false;
        }
    }
    v->buffer[v->size] = value;
    v->size++;
    return true;
}

bool d_resize(vector_d* v, int new_size){
    if (v->capacity < new_size){
        double* tmp = realloc(v->buffer, sizeof(double) * new_size);
        if (tmp == NULL){
            return false;
        }
        v->buffer = tmp;
        v->capacity = new_size;
    }
    int first_size = v->size;
    v->size = new_size;
    for (int i = first_size; i < new_size; ++i){
        v->buffer[i] = 0;
    }
    return true;
}

void d_clear(vector_d* v){
    double* old = v->buffer;
    free(old);
    v->size = v->capacity = 0;
    v->buffer = NULL;
}

void d_insert(vector_d* v, int position, double value){
    int idx = d_size(v) - 1;
    d_append(v, d_get(v, idx));
    while(idx > position){
        d_set(v, idx, d_get(v, idx-1));
        --idx;
    }
    d_set(v, position, value);
}
