#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "read.h"
#include "queue.h"
#include "token_st.h"
#include "tree_st.h"
#include "token.h"
#include "tree.h"

void print_error(char *s) {
    fprintf(stderr, "%s\n", s);
}

int priority(token t) {
    if (t.data.operator == '+' || t.data.operator == '-') {
        return 0;
    }
    if (t.data.operator == '*' || t.data.operator == '/') {
        return 1;
    }
    if (t.data.operator == '^') {
        return 2;
    }
    if (t.data.operator == '~') {
        return 3;
    }
    return -1;
}

bool left_associative(token t) {
    return !(t.data.operator == '~' || t.data.operator == '^');
}

void print_expression(tree t) {
    if (t == NULL) {
        return;
    }

    tree left = tree_get_left(t);
    tree right = tree_get_right(t);
    token tk = tree_get_value(t);

    if (tk.type == OPERATOR && tk.data.operator == '~') {
        printf("(-");
        print_token(tree_get_value(left));
        printf(")");
    } else if (tk.type == OPERATOR && tk.data.operator == '/') {
        print_expression(left);
        print_token(tk);
        printf("(");
        print_expression(right);
        printf(")");
    } else {
        if (!tree_is_empty(left)) {
            token left_tk = tree_get_value(left);
            if (tk.type == OPERATOR && left_tk.type == OPERATOR && priority(tk) > priority(left_tk)) {
                printf("(");
                print_expression(left);
                printf(")");
            } else {
                print_expression(left);
            }
        }
        print_token(tk);
        if (!tree_is_empty(right)) {
            token right_tk = tree_get_value(right);
            if (tk.type == OPERATOR && right_tk.type == OPERATOR && priority(tk) > priority(right_tk)) {
                printf("(");
                print_expression(right);
                printf(")");
            } else {
                print_expression(right);
            }
        }
    }
}

bool is_integer(double a) {
    return (double) (int) a == a;
}

tree get_sum(tree t, double power) {
    tree tmp = tree_copy(tree_get_left(t));
    if (power == 0) {
        token tk;
        tk.type = CONST;
        tk.data.value = 0;
        tmp = tree_build(tree_create(), tk, tree_create());
    }
    if (power < 0) {
        token minus_token;
        minus_token.type = OPERATOR;
        minus_token.data.operator = '~';
        tmp = tree_build(tmp, minus_token, tree_create());
    }
    char op = power > 0 ? '+' : '-';
    for (int i = 1; i < fabs(power); ++i) {
        token tk;
        tk.type = OPERATOR;
        tk.data.operator = op;
        tmp = tree_build(tmp, tk, tree_copy(tree_get_left(t)));
    }
    return tmp;
}

tree change_tree(tree t) {

    tree left = tree_get_left(t);
    tree right = tree_get_right(t);

    if (!tree_is_empty(left)) {
        left = change_tree(left);
    }

    if (tree_get_value(t).type == OPERATOR && tree_get_value(t).data.operator == '*') {
        if (tree_get_value(right).type == CONST && is_integer(tree_get_value(right).data.value)) {
            double power = tree_get_value(right).data.value;
            tree tmp = get_sum(t, power);
            return tmp;
        } else if (tree_get_value(right).type == OPERATOR && tree_get_value(right).data.operator == '~'
                   && is_integer(tree_get_value(tree_get_left(right)).data.value)) {
            double power = -tree_get_value(tree_get_left(right)).data.value;
            tree tmp = get_sum(t, power);
            return tmp;
        }
    }

    if (!tree_is_empty(right)) {
        right = change_tree(right);
    }

    return tree_build(left, tree_get_value(t), right);

}

int main() {

    int expression_counter = 1;
    queue expression;                //очередь для всех токенов
    queue_create(&expression);
    queue result;                    //очередь для постфиксной записи выражения
    queue_create(&result);
    token_stack sort;                //стек для преобразования обычной записи в постфиксную
    token_stack_create(&sort);
    tree_stack treeStack;            //дерево из постфиксной записи
    tree_stack_create(&treeStack);

    READ_SIGNAL response;            //состояние считывания

    do {
        // очещаем структуры  данных для нового выражения
        if (!queue_is_empty(&result)) { queue_clear(&result); }
        if (!token_stack_is_empty(&sort)) { token_stack_clear(&sort); }
        if (!tree_stack_is_empty(&treeStack)) { tree_stack_clear(&treeStack); }

        do {
            response = read_expression(&expression); //считываем выражение в очередь
            if (!queue_is_empty(&expression)) {
                printf("Expression №%d\n", expression_counter);
                ++expression_counter;
            }
            if (response != READ_SUCCESS && response != READ_EOE && response != READ_EOF) {
                print_error("unexpected error");
                continue;
            }
        } while (response != READ_SUCCESS && response != READ_EOE && response != READ_EOF);


        bool error = false;

        while (!queue_is_empty(&expression)) {

            if (error) {
                break;
            }

            token t = queue_pop(&expression); // идем слева направо и вставляем в очередь
            if (t.type == VARIABLE || t.type == CONST) {
                queue_push(&result, t);
                continue;
            }
            if (t.type == LEFT_BRACKET) { // заполняем вспомогательный стек скобками и операторами
                token_stack_push(&sort, t);
                continue;
            }
            if (t.type == RIGHT_BRACKET) {
                if (token_stack_is_empty(&sort)) {
                    error = true;
                } else {
                    token tmp = token_stack_pop(&sort); // (   )
                    while (tmp.type != LEFT_BRACKET && !token_stack_is_empty(&sort)) {
                        queue_push(&result, tmp);
                        tmp = token_stack_pop(&sort);
                        // todo error
//                        if (queue_is_empty(&result) && tmp.type != LEFT_BRACKET) {
//                            error = true;
//                        }
                    }
                }
                continue;
            }
            if (t.type == NONE) {
                print_error("unexpected error");
                continue;
            }
            if (t.type == OPERATOR) {
                if (token_stack_is_empty(&sort)) {
                    token_stack_push(&sort, t);
                    continue;
                }
                token operator = token_stack_pop(&sort);
                if (priority(t) > priority(operator) ||
                    operator.type == LEFT_BRACKET) { //сравниваем приоритеты и заполняем стек
                    token_stack_push(&sort, operator);
                } else if (priority(t) < priority(operator)) {
                    queue_push(&result, operator);
                } else {
                    if (left_associative(t)) {
                        queue_push(&result, operator);
                    } else {
                        token_stack_push(&sort, operator);
                    }
                }
                token_stack_push(&sort, t);
                continue;
            }
        }

        if (error) {
            print_error("unexpected error");
            continue;
        }

        while (!token_stack_is_empty(&sort)) {
            queue_push(&result, token_stack_pop(&sort));
        }

        if (queue_is_empty(&result)) {
            continue;
        }

        // построение дерева
        token tmp = queue_pop(&result);
        tree_stack_push(&treeStack, tree_build(tree_create(), tmp, tree_create()));
        while (!queue_is_empty(&result)) {
            tmp = queue_pop(&result);
            if (tmp.type == CONST || tmp.type == VARIABLE) {
                tree_stack_push(&treeStack, tree_build(tree_create(), tmp, tree_create()));
            } else {
                if (tmp.data.operator == '~') {
                    if (tree_stack_is_empty(&treeStack)) {
                        error = true;
                        continue;
                    }
                    tree left = tree_stack_pop(&treeStack);
                    tree_stack_push(&treeStack, tree_build(left, tmp, tree_create()));
                } else {
                    if (tree_stack_size(&treeStack) < 2) {
                        error = true;
                        continue;
                    }
                    tree right = tree_stack_pop(&treeStack);
                    tree left = tree_stack_pop(&treeStack);
                    tree_stack_push(&treeStack, tree_build(left, tmp, right));
                }
            }
        }

        if (tree_stack_size(&treeStack) != 1 || error) {
            print_error("unexpected error");
            continue;
        }

        tree treeExpression = tree_stack_pop(&treeStack);
        print_expression(treeExpression);
        printf("\n");
        printf("--------------------------------------------------------\n");
        tree_print(treeExpression, 0);
        printf("--------------------------------------------------------\n");
        tree newTreeExpression = change_tree(treeExpression);
        print_expression(newTreeExpression);
        printf("\n");
        printf("========================================================\n");

    } while (response != READ_EOF);

    queue_destroy(&result);
    token_stack_destroy(&sort);
    tree_stack_destroy(&treeStack);
    queue_destroy(&expression);
}