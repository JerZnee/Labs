#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"

//specification_begin
tree create_empty_tree(){
    return NULL;
}

void destroy(tree t){
    free(t);
}

tree build_tree(tree left, int val, tree right){
    tree tmp = malloc(sizeof(node));
    tmp->left = left;
    tmp->val = val;
    tmp->right = right;
    return tmp;
}

bool tree_is_empty(tree t){
    return t == NULL;
}

int get_root(tree t){
    return t->val;
}

tree get_left(tree t){
    return t->left;
}

tree get_right(tree t){
    return t->right;
}

int remove_leftmost(tree *t){
    if((*t)->left != NULL){
        return remove_leftmost(&(*t)->left);
    }else {
        int tmp = (*t)->val;
        tree a = (*t)->right;
        free(*t);
        *t = a;
        return tmp;
    }
}
tree delete_rightmost(tree t, int *new_root){
    if(!tree_is_empty(t->right)){
        tree tmp = build_tree(get_left(t),get_root(t), delete_rightmost(get_right(t), new_root));
        destroy(t);
        return tmp;
    }else {
        *new_root = get_root(t);
        return get_left(t);
    }
}
//specification_end

//function
void clear_tree_recursive(tree t){
    if(t != NULL) {
        clear_tree_recursive(t->left);
        clear_tree_recursive(t->right);
        free(t);
    }
}

tree insert(tree t, int val){
    if(tree_is_empty(t)){
        return build_tree(create_empty_tree(), val, create_empty_tree());
    } else if(val < get_root(t)) {
        tree tmp = build_tree(insert(get_left(t), val), get_root(t), get_right(t));
        return tmp;
    } else if(val > get_root(t)){
        tree tmp = build_tree(get_left(t), get_root(t),insert(get_right(t), val));
        return tmp;
    } else {
        return t;
    }
}

tree* find(tree *t, int val){
    if(*t == NULL){
        return NULL;
    } else if(val < (*t)->val){
        return find(&(*t)->left, val);
    } else if(val > (*t)->val){
        return find(&(*t)->left, val);
    } else{
        return t;
    }
}

void remove_(tree *t){
    if((*t)->left == NULL){
        tree a = (*t)->right;
        free(*t);
        *t = a;
    } else if((*t)->right == NULL){
        tree a = (*t)->left;
        free(*t);
        *t = a;
    } else{
        int n = remove_leftmost(&(*t)->right);
        (*t)->val = n;
    }
}

tree remove_el(tree t, int val) {
    if(tree_is_empty(t)){
        return t;
    } else if(val < get_root(t)){
        tree tmp = build_tree(remove_el(get_left(t), val), get_root(t), get_right(t));
        destroy(t);
        return tmp;
    }else if(val > get_root(t)){
        tree tmp = build_tree(get_left(t), get_root(t), remove_el(get_right(t), val));
        destroy(t);
        return tmp;
    }else{
        if(tree_is_empty(get_right(t))){
            tree tmp = get_left(t);
            destroy(t);
            return tmp;
        } else if(tree_is_empty(get_left(t))){
            tree tmp = get_right(t);
            destroy(t);
            return tmp;
        }else {
            int new_root;
            tree new_left = delete_rightmost(get_left(t), &new_root);
            tree tmp = build_tree(new_left, new_root, get_right(t));
            destroy(t);
            return tmp;
        }
    }
}