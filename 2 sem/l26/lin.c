#include <stdio.h>
#include <stdlib.h>
#include "lin.h"

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
List *create() {
    List *tmp = (List *) malloc(sizeof(List));
    tmp->size = 0;
    tmp->arr = NULL;
    return tmp;
}

void printList(const List *list) {
    index_t node_idx = getElement(list, 0);
    while(node_idx != INVALID_INDEX){
        printf("%f ", get(list, node_idx)->val);
        node_idx = get(list, node_idx)->next_index;
    }
    printf("\n");
}

void deleteList(List *list) {
    for (int i = 0; i < list->size; ++i) {
        Node *node = get(list, i);
        free(node);
    }
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
//ищет следующий элемент

index_t getLast(List *list) {
    if (list == NULL) {
        return INVALID_INDEX;
    }
    index_t index = list->first;
    Node *head = list->arr[index];
    while (head->next_index != INVALID_INDEX) {
        index = head->next_index;
        head = list->arr[index];
    }
    return index;
}

Node *next(const List *list, Node *cur){
    return list->arr[cur->next_index];
}

index_t getElement(const List* list, index_t index){  // index - тот, что по счету в списке
    Node *node = list->arr[list->first];
    index_t cur_idx, ans_idx = list->first;

    for (cur_idx = 0; cur_idx < index; ++cur_idx) {
        ans_idx = node->next_index;
        node = next(list, node);
    }
    return ans_idx;
}

Node* get(const List *list, index_t index){ // index - тот, что в массиве
    return list->arr[index];
}

void set(List *list, index_t index, float val){  // index - тот, что в массиве
    get(list, index)->val = val;
}

void setElement(List *list, index_t index, float val){  // index - тот, что в списке
    index_t index_in_array = getElement(list, index);
    set(list, index_in_array, val);
}

size_t length(const List *list){
    return list->size;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
void push(List *list, float data) {
    index_t last_index;
    index_t new_index = (index_t)list->size;
    //ищем индекс последнего элемента
    if(list->size == 0){
        last_index = 0;
        list->arr = (Node**)malloc(sizeof(Node*));
    } else{
        last_index = getLast(list);  // индекс последнего элемента(он не последний в массиве)
        list->arr = realloc(list->arr, sizeof(Node*) * (list->size+1));
    }
    list->arr[new_index] = (Node*) malloc(sizeof(Node)); // выделение памяти

    //присваиваем старому указателю на следующий индекс новый индекс
    list->arr[last_index]->next_index = new_index;
    //присваиваем новому индексу значение и указатель на следующий
    list->arr[new_index]->next_index = INVALID_INDEX;
    list->arr[new_index]->val = data;
    list->size++;
}

void insert(List *list, index_t index, float val) {
    index_t new_index = (index_t)list->size; // индекс нового элемента
    index_t i = getElement(list, index);  // номер в массиве
    //Находим нужный элемент. Если вышли за пределы списка, то выходим из цикла,
    //ошибка выбрасываться не будет, произойдёт вставка в конец

    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->val = val;

    Node *cur_node = get(list, i); // current node - текущий узел

    //Если это не последний элемент, то next перекидываем на следующий узел
    if(cur_node->next_index != INVALID_INDEX){
        tmp->next_index = cur_node->next_index;
    } else{  // иначе на INVALID_INDEX
        tmp->next_index = INVALID_INDEX;
    }
    cur_node->next_index = new_index;

    // увеличиваем массив
    list->arr = realloc(list->arr, (list->size + 1) * sizeof(Node**));

    // добавляем элемент
    list->arr[new_index] = tmp;

    // увеличиваем размер списка
    list->size++;
}

float pop(List *list) {
    index_t cur_index;
    if (list == NULL) {
        exit(-1);
    }
    cur_index = list->first;
    index_t last_index = getLast(list);
    Node* node = list->arr[cur_index];
    while(node->next_index != last_index){
        cur_index = node->next_index;
        node = next(list, node);
    }

    list->arr[cur_index]->next_index = INVALID_INDEX;
    Node *last_node = get(list, last_index);

    float val = last_node->val;
    free(last_node);

    list->size--;
    return val;
}

