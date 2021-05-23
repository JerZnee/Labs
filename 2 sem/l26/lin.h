#pragma once

typedef int index_t; // index_type
static const index_t INVALID_INDEX = -1;

typedef struct{
    float  val;
    index_t next_index;
} Node;

typedef struct {
    index_t first; // номер первого элемента
    Node** arr;
    size_t size;
} List;


List *create();
void printList(const List *list);
void deleteList(List *list);

index_t getLast(List *list);
Node *next(const List *list, Node *cur);
size_t length(const List *list);
index_t getElement(const List* list, index_t index);
Node *get(const List * list, index_t n);

void push(List *list, float data);
void insert(List *list, index_t n, float val);
float pop(List *list);

