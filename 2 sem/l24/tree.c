#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "token.h"
#include "tree.h"

tree tree_create() { return NULL; }

void tree_destroy(tree t) { free(t); }

bool tree_is_empty(tree t) { return t == NULL; }

token tree_get_value(tree t) { return t->value; }

tree tree_get_left(tree t) { return t->left; }

tree tree_get_right(tree t) { return t->right; }

tree tree_build(tree left, token value, tree right) {
    tree tmp = malloc(sizeof(node));
    tmp->left = left;
    tmp->value = value;
    tmp->right = right;
    return tmp;
}

void tree_clear(tree t) {
    if (tree_is_empty(t)) {
        return;
    }
    if (!tree_is_empty(tree_get_left(t))) {
        tree_clear(tree_get_left(t));
    }
    if (!tree_is_empty(tree_get_right(t))) {
        tree_clear(tree_get_right(t));
    }
    tree_destroy(t);
}

void tree_print(tree t, int h) {
    if (!tree_is_empty(tree_get_right(t))) {
        tree_print(tree_get_right(t), h + 2);
    }
    for (int i = 0; i < h; ++i) {
        printf(".");
    }
    token tmp = tree_get_value(t);
    if (tmp.type == CONST) {
        printf("%lf\n", tmp.data.value);
    } else if (tmp.type == VARIABLE) {
        printf("%s\n", tmp.data.name);
    } else {
        printf("%c\n", tmp.data.operator);
    }
    if (!tree_is_empty(tree_get_left(t))) {
        tree_print(tree_get_left(t), h + 2);
    }
}


tree tree_copy(tree t){
    if(t == NULL){
        return NULL;
    }
    tree copy = (node*)malloc(sizeof(node));
    copy->value = t->value;
    copy->left = tree_copy(t->left);
    copy->right = tree_copy(t->right);
    return copy;
}

