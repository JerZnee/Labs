#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "list_it.h"
#include "iter.h"
#include "list.h"
int barrie_el = 0;

void l_create(list *l){
    l->cap = 20;
    l->buf = malloc(l->cap * sizeof(list_el));
    l->buf[barrie_el].prev_idx = barrie_el;
    l->buf[barrie_el].next_idx = barrie_el;
    for(int i = 1; i < l->cap - 1; i++){
        l->buf[i].next_idx = i + 1;
    }
    l->buf[l->cap - 1].next_idx = barrie_el;
    l->top_empty_idx = 1;
    l->size = 0;
}

void l_destroy(list *l){ //постепенный поп
    free(l->buf);
    l->cap = 0;
    l->top_empty_idx = 1;
    l->size = 0;
}

bool l_is_empty(list l){
    return l.size == 0;
}

unsigned int l_get(list l, unsigned long int i){
    int cur_idx = l.buf[barrie_el].next_idx;
    while(i > 0){
        cur_idx = l.buf[cur_idx].next_idx;
    }
    return l.buf[cur_idx].val;
}

void l_print(list l){
    for(iter it = iter_begin(&l); !iter_equal(it, iter_end(&l)); it = iter_next(it)){
        printf("%ld ", iter_get_val(it));
    }
    printf("\n");
}

int l_size(list l){
    return l.size;
}

static int l_cap(list l){
    return l.cap;
}

static bool l_grow_buffer(list *l){
    int tmp = l->cap * 3 / 2;
    list_el* newd = realloc(l->buf, tmp * sizeof(list_el));
    if(newd == NULL){
        fprintf(stderr, "Not enough memory\n");
        return false;
    }
    l->buf = newd;
    l->top_empty_idx = l->cap;
    for(int i = l->cap; i < tmp - 1; i++){
        l->buf[i].next_idx = i + 1;
    }
    l->buf[tmp - 1].next_idx = barrie_el;
    l->cap = tmp;
    return true;
}

void l_insert(list *l, unsigned long int i, unsigned long int val){
    if(l_size(*l) + 2 > l_cap(*l)){
        if(!l_grow_buffer(l)){
            return;
        }
    }
    unsigned long int cur_idx = barrie_el;
    while(i > 0){
        cur_idx = l->buf[cur_idx].next_idx;
        i--;
        if(cur_idx == barrie_el){
            fprintf(stderr, "Index out of bounds\n");
            return;
        }
    }
    iter it = (iter){l, cur_idx};
    iter_insert_before(&it, val);
}

void l_remove(list *l, int i){
    int cur_idx = barrie_el;
    if(i < 0){
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    while(i > 0){
        cur_idx = l->buf[cur_idx].next_idx;
        i--;
        if(cur_idx == barrie_el){
            fprintf(stderr, "Index out of bounds\n");
            return;
        }
    }
    iter it = (iter){l, cur_idx};
    iter_remove(&it);
}

void l_push_front(list *l, unsigned long int val){
    l_insert(l, 0, val);
}

void l_push_back(list *l, unsigned long int val){
    l_insert(l, l_size(*l), val);
}

void l_pop_front(list *l){
    l_remove(l, 0);
}

void l_pop_back(list *l){
    l_remove(l, l_size(*l) - 1);
}

void l_iter_swap(iter* a, iter* b){
    unsigned long int t = iter_get_val(*b);
    iter_set_val(b, iter_get_val(*a));
    iter_set_val(a, t);
}

void l_reverse(list *l){
    iter front = iter_begin(l);
    iter back = iter_prev(iter_end(l));
    for(int i = 0; i < l_size(*l) / 2; i++){
        l_iter_swap(&front, &back);
        front = iter_next(front);
        back = iter_prev(back);
    }
}
