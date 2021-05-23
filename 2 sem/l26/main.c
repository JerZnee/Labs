#include <stdio.h>
#include <stdlib.h>
#include "lin.h"

void permute(List *list, Node *node) {
    Node *next_node = next(list, node);
    if (node->val <= next_node->val) {
        float tmp = next_node->val; // tmp = get(i+1)
        next_node->val = node->val; // set(i+1, get(i))
        node->val = tmp;  // set(i, tmp)
        return;
    }
}

List *bubbleSort(List *list) {
    int len = (int)length(list);

    if (len == 0) {
        return NULL;
    } else if (len == 1) {
        return list;
    }
    List *ans = create();
    for (int i = len - 1; i >= 0; --i) {
        Node *cur_node = get(list, getElement(list, 0));
        for (int j = 0; j < i; ++j) {
            permute(list, cur_node);
            cur_node = next(list, cur_node);
        }
        push(ans, cur_node->val);
    }
    return ans;
}

int main() {
    List *list = create();
    float n;
    scanf("%f", &n);
    push(list, n);
    while (scanf("%f", &n) > 0) {
        push(list, n);
    }
    List *ans = bubbleSort(list);
    printList(ans);
    deleteList(list);
    return 0;
}
