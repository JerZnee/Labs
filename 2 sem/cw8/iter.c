#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "list_it.h"
#include "iter.h"
#include "list.h"

int barrier_el = 0;

unsigned long int iter_get_val(iter it){
    return it.list->buf[it.prev].val;
}

void iter_set_val(iter* it, unsigned long int val){
    it->list->buf[it->prev].val = val;
}

iter iter_next(iter it){
    return (iter){it.list, it.list->buf[it.prev].next_idx};
}

iter iter_prev(iter it){
    return (iter){it.list, it.list->buf[it.prev].prev_idx};
}

bool iter_equal(iter it1, iter it2){
    return it1.prev == it2.prev && it1.list == it2.list;
}

iter iter_begin(list *l){
    return (iter){l, l->buf[barrier_el].next_idx};
}

iter iter_last_element(list *l){
    return iter_prev(iter_end(l));
}

iter iter_end(list *l){
    return (iter){l, barrier_el};
}

list_el *link_end(list *l){
    return &l->buf[barrier_el];
}

void iter_insert_before(iter *it, unsigned long int val){
    it->list->size++;
    int to_ins = it->list->top_empty_idx;
    it->list->top_empty_idx = it->list->buf[to_ins].next_idx;
    it->list->buf[to_ins].val = val;
    if(iter_equal(*it, iter_end(it->list))){
        it->list->buf[to_ins].prev_idx = barrier_el;
        it->list->buf[to_ins].next_idx = it->list->buf[barrier_el].next_idx;
        it->list->buf[it->list->buf[barrier_el].next_idx].prev_idx = to_ins;
        it->list->buf[barrier_el].next_idx = to_ins;
    } else{
        it->list->buf[to_ins].prev_idx = it->prev;
        it->list->buf[to_ins].next_idx = it->list->buf[it->prev].next_idx;
        it->list->buf[it->list->buf[it->prev].next_idx].prev_idx = to_ins;
        it->list->buf[it->prev].next_idx = to_ins; //~~~~~
    }
}

void iter_remove(iter *it){
    if(!it->list->size){
        return;
    }
    it->list->size--;
    if(iter_equal(*it, iter_end(it->list))){
        int to_del = it->list->buf[barrier_el].next_idx;
        it->list->buf[barrier_el].next_idx = it->list->buf[to_del].next_idx;
        it->list->buf[it->list->buf[barrier_el].next_idx].prev_idx = barrier_el;
        it->list->buf[to_del].next_idx = it->list->top_empty_idx;
        it->list->top_empty_idx = to_del;
    } else{
        int to_del = it->list->buf[it->prev].next_idx;
        it->list->buf[it->list->buf[to_del].prev_idx].next_idx = it->list->buf[to_del].next_idx;
        it->list->buf[it->list->buf[to_del].next_idx].prev_idx = it->list->buf[to_del].prev_idx;
        it->list->buf[to_del].next_idx = it->list->top_empty_idx;
        it->list->top_empty_idx = to_del;
    }
}