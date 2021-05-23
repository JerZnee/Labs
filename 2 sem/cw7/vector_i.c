#include <stdlib.h>
#include <stdbool.h>
#include "vector_i.h"

void v_create(vector* v){
    v->size     = 0;
    v->capacity = 0;
    v->buffer   = NULL;
}

void v_destroy(vector* v){
    v->size     = 0;
    v->capacity = 0;
    free(v->buffer);
    v->buffer   = NULL;
}

int v_size(vector* v){
    return v->size;
}

int v_get(vector* v, int position){
    return v->buffer[position];
}

void v_set(vector* v, int position, int value){
    v->buffer[position] = value;
}

bool grow_buffer(vector* v){
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

bool v_append(vector* v, int value){
    if (v->size >= v->capacity){
        if (!grow_buffer(v)){
            return false;
        }
    }
    v->buffer[v->size] = value;
    v->size++;
    return true;
}

bool v_resize(vector* v, int new_size){
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

void v_clear(vector* v){
    double* old = v->buffer;
    free(old);
    v->size = v->capacity = 0;
    v->buffer = NULL;
}

void v_insert(vector* v, int position, int value){
    int idx = v_size(v) - 1;
    v_append(v, v_get(v, idx));
    while(idx > position){
        v_set(v, idx, v_get(v, idx-1));
        --idx;
    }
    v_set(v, position, value);
}
