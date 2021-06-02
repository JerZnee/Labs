#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "list_it.h"
#include "list.h"
#include "iter.h"

void list_create(List* l){
    l->barrier_elem = 0;
    l->capacity = 10;
    l->buffer = malloc(l->capacity * sizeof(list_elem));
    l->buffer[l->barrier_elem].prev_index = l->barrier_elem;
    l->buffer[l->barrier_elem].next_index = l->barrier_elem;

    for(int i = 1; i < l->capacity - 1; i++){
        l->buffer[i].next_index = i + 1;
    }

    l->buffer[l->capacity - 1].next_index = l->barrier_elem;
    l->first_empty_index = 1;
    l->size = 0;
}

void list_destroy(List* l){
    free(l->buffer);
    l->capacity = 0;
    l->first_empty_index = 1;
    l->size = 0;
}

bool list_is_empty(List* l){
    return l->size == 0;
}

float list_get(List* l, int i){
    int cur_idx = l->buffer[l->barrier_elem].next_index;
    while (i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        --i;
    }
    return l->buffer[cur_idx].value;
}

void list_print(List* l){
    for (iterator it = iter_begin(l); !iter_is_equal(it, iter_end(l)); it = iter_next(it)){
        printf("%.1f ", iter_get_value(it));
    }
    printf("\n");
}

int list_size(List* l){
    return l->size;
}

bool list_grow_buffer(List* l){
    int new_capacity = l->capacity * 3 / 2;
    if (new_capacity < 10){
        new_capacity = 10;
    }
    list_elem* tmp = realloc(l->buffer, new_capacity * sizeof(list_elem));
    if(tmp == NULL){
        return false;
    }
    l->buffer = tmp;
    l->first_empty_index = l->capacity;
    for(int i = l->capacity; i < new_capacity - 1; i++){
        l->buffer[i].next_index = i + 1;
    }
    l->buffer[new_capacity - 1].next_index = l->barrier_elem;
    l->capacity = new_capacity;
    return true;
}

void list_insert(List* l, int i, float val){
    if(l->size + 2 > l->capacity){
        if(!list_grow_buffer(l)){
            return;
        }
    }
    int cur_idx = l->barrier_elem;
    while(i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        i--;
    }
    iterator it = (iterator){l, cur_idx};
    iter_insert_before(&it, val);
}

void list_delete(List* l, int i){
    int cur_idx = l->barrier_elem;
    while(i > 0){
        cur_idx = l->buffer[cur_idx].next_index;
        i--;
    }
    iterator it = (iterator){l, cur_idx};
    iter_delete(&it);
}

void list_push_front(List* l, float val){
    list_insert(l, 0, val);
}

void list_push_back(List* l, float val){
    list_insert(l, list_size(l), val);
}

void list_pop_front(List* l){
    list_delete(l, 0);
}

void list_pop_back(List* l){
    list_delete(l, list_size(l) - 1);
}

bool list_sorted(List* l){
    if (list_size(l) <= 2){
        return true;
    }
    iterator left = iter_begin(l);
    iterator right = iter_next(left);
    while (iter_get_value(left) == iter_get_value(right)){
        right = iter_next(right);
        if (iter_is_equal(right, iter_end(l))){
            return true;
        }
    }
    bool increase;
    if (iter_get_value(left) < iter_get_value(right)){
        increase = true;
    } else {
        increase = false;
    }
    left = right;
    right = iter_next(right);
    while (!iter_is_equal(right, iter_end(l))){
        if (iter_get_value(left) < iter_get_value(right)){
            if (!increase){
                return false;
            }
        } else if (iter_get_value(left) > iter_get_value(right)){
            if (increase){
                return false;
            }
        }
        left = right;
        right = iter_next(right);
    }
    return true;
}