#include <stdbool.h>
#include "list_it.h"
#include "iter.h"


float iter_get_value(iterator it){
    return it.list->buffer[it.prev].value;
}

void iter_set_value(iterator* it, float value){
    it->list->buffer[it->prev].value = value;
}

iterator iter_next(iterator it){
    return (iterator){it.list, it.list->buffer[it.prev].next_index};
}

iterator iter_prev(iterator it){
    return (iterator){it.list, it.list->buffer[it.prev].prev_index};
}

bool iter_is_equal(iterator it1, iterator it2){
    return it1.prev == it2.prev && it1.list == it2.list;
}

iterator iter_begin(List* l){
    return (iterator){l, l->buffer[l->barrier_elem].next_index};
}

iterator iter_end(List* l){
    return (iterator){l, l->barrier_elem};
}

iterator iter_last_elem(List* l){
    return iter_prev(iter_end(l));
}

void iter_insert_before(iterator *it, float val){
    it->list->size++;
    int insert_to = it->list->first_empty_index;
    it->list->first_empty_index = it->list->buffer[insert_to].next_index;
    it->list->buffer[insert_to].value = val;
    if(iter_is_equal(*it, iter_end(it->list))){
        it->list->buffer[insert_to].prev_index = it->list->barrier_elem;
        it->list->buffer[insert_to].next_index = it->list->buffer[it->list->barrier_elem].next_index;
        it->list->buffer[it->list->buffer[it->list->barrier_elem].next_index].prev_index = insert_to;
        it->list->buffer[it->list->barrier_elem].next_index = insert_to;
    } else{
        it->list->buffer[insert_to].prev_index = it->prev;
        it->list->buffer[insert_to].next_index = it->list->buffer[it->prev].next_index;
        it->list->buffer[it->list->buffer[it->prev].next_index].prev_index = insert_to;
        it->list->buffer[it->prev].next_index = insert_to;
    }
}

void iter_delete(iterator *it){
    if(!it->list->size){
        return;
    }
    it->list->size--;
    if(iter_is_equal(*it, iter_end(it->list))){
        int to_del = it->list->buffer[it->list->barrier_elem].next_index;
        it->list->buffer[it->list->barrier_elem].next_index = it->list->buffer[to_del].next_index;
        it->list->buffer[it->list->buffer[it->list->barrier_elem].next_index].prev_index = it->list->barrier_elem;
        it->list->buffer[to_del].next_index = it->list->first_empty_index;
        it->list->first_empty_index = to_del;
    } else{
        int to_del = it->list->buffer[it->prev].next_index;
        it->list->buffer[it->list->buffer[to_del].prev_index].next_index = it->list->buffer[to_del].next_index;
        it->list->buffer[it->list->buffer[to_del].next_index].prev_index = it->list->buffer[to_del].prev_index;
        it->list->buffer[to_del].next_index = it->list->first_empty_index;
        it->list->first_empty_index = to_del;
    }
}