#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "list_it.h"
#include "iter.h"

void swap(iterator* first, iterator* second) {
    float tmp = iter_get_value(*first); // tmp = get(i+1)
    iter_set_value(first, iter_get_value(*second)); // set(i+1, get(i))
    iter_set_value(second, tmp);  // set(i, tmp)
}

List *bubbleSort(List *list) {
    int len = list_size(list);

    if (len == 0) {
        return NULL;
    } else if (len == 1) {
        return list;
    }
    List* ans = malloc(sizeof(List));
    list_create(ans);
    for (int i = 1; i < len; i++) {
        iterator first = iter_begin(list);
        iterator second = iter_next(first);
        for (int j = 0; j < len-i; j++) {
            if(iter_get_value(first) > iter_get_value(second)){
                swap(&first, &second);
            }
            first = second;
            second = iter_next(second);
        }
        list_push_front(ans, iter_get_value(first));
    }
    return ans;
}

int main() {
    List list;
    list_create(&list);
    float n;
    while (scanf("%f", &n) > 0) {
        list_push_back(&list, n);
    }
    List* ans = bubbleSort(&list);
    list_print(ans);
    list_destroy(ans);
    list_destroy(&list);
    return 0;
}
