#ifndef L23_TREE_H
#define L23_TREE_H
typedef struct node node;
struct node{
    int val;
    node *left;
    node *right;
};
typedef node* tree;
tree create_empty_tree();
void destroy(tree t);
tree build_tree(tree left, int val, tree right);
bool tree_is_empty(tree t);
int get_root(tree t);
tree get_left(tree t);
tree get_right(tree t);
int remove_leftmost(tree *t);
tree delete_rightmost(tree t, int *new_root);
void clear_tree_recursive(tree t);
tree insert(tree t, int val);
tree* find(tree *t, int val);
//void remove_(tree *t);
tree remove_el(tree t, int val);
#endif //L23_TREE_H
