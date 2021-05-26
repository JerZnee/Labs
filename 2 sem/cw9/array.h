#ifndef LAB_ARRAY_H
#define LAB_ARRAY_H


typedef char* string;
typedef uint64_t int_8;

typedef struct node{
    int_8 key;
    string data;
} node;

typedef struct array{
    node *array;
    size_t len, capacity;
} array;

array* array_create(const int_8* keys, string* data, size_t count);
void array_push_back(array* arr, node n);
node* array_back(array* arr);
void array_pop_back(array* arr);
void array_free(array* l);
void array_node_swap(node* arr, size_t ind1, size_t ind2);
void array_print(array *arr);
void array_quick_sort(array* arr);
void array_shuffle(array *arr);
void array_reverse(array *arr);
#endif //LAB_ARRAY_H