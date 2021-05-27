#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "array.h"

array* array_create(const int_8* keys, string* data, size_t count){
    array* arr = malloc(sizeof(array));
    arr->capacity = (arr->len = count) * 2;

    arr->array = calloc(arr->capacity, sizeof(node));
    for (int i = 0; i < count; ++i) {
        arr->array[i].key = keys[i];
        arr->array[i].data = data[i];
    }
    return arr;
}

void array_push_back(array* arr, node n){
    if(arr->capacity == arr->len){
        arr->capacity *= 2;
        arr->array = realloc(arr->array, arr->capacity);
    }
    arr->array[arr->len] = n;
    arr->len++;
}

node* array_back(array* arr){
    if(arr->len)
        return arr->array + arr->len-1;
    return NULL;
}

void array_pop_back(array* arr){
    if(arr->len) arr->len--;
}


void array_free(array * l){
    free(l->array);
    free(l);
}

void array_node_swap(node* arr, size_t ind1, size_t ind2){
    node tmp = arr[ind1];
    arr[ind1] = arr[ind2];
    arr[ind2] = tmp;
}

size_t array_hoar_quick_sort_partition(node* arr, size_t low, size_t high){
    int_8 pivot = arr[(high+low) / 2].key;
    size_t i = low-1 ,j = high+1;
    while(true){
        do{
            i++;
        } while (arr[i].key < pivot);

        do {
            j--;
        } while (arr[j].key > pivot);
        if(i >= j) return j;

        array_node_swap(arr, i, j);
    }
}

void _array_quick_sort(node* arr, size_t low, size_t high){
    if(low < high){
        size_t pivot = array_hoar_quick_sort_partition(arr, low, high);
        _array_quick_sort(arr, low, pivot);
        _array_quick_sort(arr, pivot+1, high);
    }
}

void array_quick_sort(array* arr){
    _array_quick_sort(arr->array, 0, arr->len-1);
}

void array_print(array *arr){
    for (size_t i = 0; i < arr->len; ++i) {
        printf("|%3lu|%s ", arr->array[i].key, arr->array[i].data);
    }
    puts("");
}

void array_shuffle(array *arr){
    for (size_t i = 0; i < arr->len-1; ++i) {
        for (size_t j = i+1; j < arr->len; ++j) {
            if((unsigned long)rand() & 1u){
                array_node_swap(arr->array, i, j);
            }
        }
    }
}

void array_reverse(array *arr){
    for (size_t i = 0; i < arr->len/2; ++i) {
        array_node_swap(arr->array, i, arr->len - i - 1);
    }
}
