#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <ctype.h>
#include "tree.h"
#include "vector_c.h"
typedef struct{
    tree t;
    bool a;
}su;

typedef enum {
    cat = 0,
    dog = 1,
    lion = 2,
    tiger = 3,
    bear = 4,
    fox = 5,
    hare = 6,
    badger = 7,
    monkey = 8,
    snake = 9,
    shark//10
} animals;

const static struct {
    animals     val;
    const char *str;
} conversion [] = {
        {cat, "cat"},
        { dog, "dog"},
        {lion, "lion"},
        {tiger, "tiger"},
        {bear, "bear"},
        {fox, "fox"},
        {hare, "hare"},
        {badger, "badger"},
        {monkey, "monkey"},
        {snake, "snake"},
        {shark, "shark"},
        };

animals str_to_enum(const char *str){
    for (int j = 0; j < sizeof(conversion)/sizeof (conversion[0]); ++j) {
        if(!strcmp(str, conversion[j].str))
            return conversion[j].val;
    }
    return -100;
}

const char * int_to_enum(int val){
    for (int j = 0; j < sizeof(conversion)/sizeof (conversion[0]); ++j) {
        if(val == conversion[j].val)
            return conversion[j].str;
    }
    return "";
}

void strip_blank_back(char *str) { //убирает пробелы и \n в конце строки
    size_t str_len = strlen(str);
    while (isblank(str[str_len - 1]) || isspace(str[str_len - 1])) {
        str[str_len - 1] = '\0';
        str_len--;
    }
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

int calc_depth(tree t) {
    if (tree_is_empty(t)) return 0;
    int a = 0, b = 0;
    if (!tree_is_empty(t->left)) {
        a = calc_depth(t->left);
    }
    if (!tree_is_empty(t->right)) {
        b = calc_depth(t->right);
    }
    return max(a, b) + 1;
}

int get_width_depth(tree t, int c) {
    if (tree_is_empty(t)) return 0;
    if (c > 0) {
        return get_width_depth(t->left, c - 1) + get_width_depth(t->right, c - 1);
    }
    return 1;
}

int calc_ans(tree t) {
    int depth = calc_depth(t);
    int ans = 1, ans_num = 0;
    if(tree_is_empty(t)) {
    	return 0;
    }
    for (int i = 0; i < depth; ++i) {
        int dans = get_width_depth(t, i);
        if (dans > ans) {
            ans_num = i;
            ans = dans;
        }
    }
    return ans_num + 1;
}

void _tree_print(tree t, int depth) {
    if (t != NULL) {
        for (int i = 0; i < depth; ++i) {
            printf("\t");
        }
        const char * str;
        str = int_to_enum(t->val);
        printf("%s", str);
        printf("\n");
        if(!tree_is_empty(t->right)) {
            printf("r: ");
            _tree_print(t->right, depth + 1);
        }
        if(!tree_is_empty(t->left)){
            printf("l: ");
            _tree_print(t->left, depth + 1);
        }
    }
}

void print(tree t) {
    _tree_print(t, 0);
}

tree add(tree t, vector *v) {
    if (v_size(v) < 1) {
        puts("Вы забыли указать, что нужно добавить");
        return NULL;
    }
    for (int j = 0; j < v_size(v); ++j) {
        if (strcmp(v_get(v, j), "") == 0) {
            continue;
        }
        int val = str_to_enum(v_get(v, j));
        if (val == -100) {
            puts("Такой строки нет в справке");
            return NULL;
        }
        t = insert(t, val);
    }
    return t;
}

su delete(tree t, vector *v) {
    su lo;
    lo.a = true;
    lo.t = NULL;
    if (v_size(v) < 1) {
        puts("Вы забыли указать, что нужно удалить");
        return lo;
    }
    for (int j = 0; j < v_size(v); ++j) {
        int val = str_to_enum(v_get(v, j));
        if (val == -100) {
            puts("Такой строки нет в справке");
            return lo;
        }
        t = remove_el(t, val);
        lo.t = t;
        if (t == NULL) {
            lo.a = false;
            destroy(t);
            puts("Вы удалили дерево");
            return lo;
        }
    }
    return lo;
}

//При входе в программу
void help_0() {
    puts("Таблица значений:\ncat = 0,\ndog = 1,\nlion = 2\ntiger = 3,\nbear = 4,\nfox = 5,\nhare = 6,\nbadger = 7,\nmonkey = 8,\nsnake = 9,\nshark = 10");
    puts("Программа работает с двоичным деревом поиска, узлы которо элементы типа enum. Ознакомьтесь с командами:\n");
    puts("\t\tКоманды, которым нужны аргументы - животные из таблицы, приведенной выше:\nadd <strings> - добавляет указанных животных в дерево\ndelete <strings> - удаляет указанных животных из дерева");
    puts("\t\tКоманды, которым не нужны аргументы:\nprint - выводит дерево\nfind - ищет уровень с максимальынм количеством узлов\nhelp - выводит справку подробную справку\nexit - завершает программу\n");
}

void help_1() {
    puts("Таблица значений:\ncat = 0,\ndog = 1,\nlion = 2\ntiger = 3,\nbear = 4,\nfox = 5,\nhare = 6,\nbadger = 7,\nmonkey = 8,\nsnake = 9,\nshark = 10");
    puts("Программа работает с двоичным деревом поиска, узлы которо элементы типа enum. Ознакомьтесь с командами подробнее:\n");
    puts("\t\tКоманды, которым нужны агрументы - животные из таблицы, указанной выше:");
    puts("\tadd <strings> - добавляет в двоичное дерево поиска животных, указанных как агрументы к команде, введенные через пробел");
    puts("Важно! Если вы введете add без аргументов, то ничего не добавится.\nЕсли вы ввели животное, которое уже есть в дереве, оно не добавится снова.");
    puts("\tdelete <strings> - удаляет из дерева животных, указанных как агрументы к команде, введенные через пробел");
    puts("Важно!Если вы введете delete без аргументов, то ничего не удалится.\nЕсли вы ввели животное, которого нет в дереве, ничего не произойдет.");
    puts("\t\tКоманды, которым не нужны агрументы:");
    puts("\tprint - выводит дерево\n\tfind - ищет уровень с максимальынм количеством узлов\n\thelp - выводит справку\n\texit - завершает программу");
    puts("Важно!Если вы введете аргументы к этим командам, то они выполнятся, игнорируя аргументы");
}

void h_command_is_not_found() {
    puts("Введенной Вами команды не существует, попробуйте снова.\nДля просмотра функциональной справки введите 'help'.");
}

int main() {
    help_0();
    tree t = create_empty_tree();
    while (true) {
        printf(">>> ");
        char *str = NULL, *arg = NULL, *cmd;
        size_t buf_size = 0;
        if (getline(&str, &buf_size, stdin) > 0) {//считывание строки до \n, включая \n
            strip_blank_back(str);
            cmd = strtok(str, " "); // считываем аргументы введенной команды
            if (cmd != NULL) {
                arg = strtok(NULL, " ");
            } else {
                cmd = str;
            }

            vector *v = malloc(sizeof(vector));
            v_create(v, 0);
            while (arg != NULL) { // добавляем все аргументы команды в вектор
                v_push(v, arg);
                arg = strtok(NULL, " ");
            }
            // Сравниваем команды
            if (strcmp(cmd, "add") == 0) {
                tree new_t = add(t, v);
                if (v_size(v) < 1) {
                }
                if (new_t == NULL) {
                    puts("Что-то пошло не так, элемент не был добавлен в дерево");
                } else {
                    t = new_t;
                    puts("Выполнено успешно");
                }
            } else if (strcmp(cmd, "print") == 0) {
                print(t);
            } else if (strcmp(cmd, "delete") == 0) {
                su del = delete(t, v);
                if (v_size(v) < 1) {
                }
                if (del.t == NULL && del.a == true) {
                    puts("Что-то пошло не так, элемент не был удален из дерева или вы удалили дерево.");
                }else if(del.t == NULL && del.a == false) {
                    puts("Выполнено успешно");
                    t = NULL;
                }else{
                    t = del.t;
                    puts("Выполнено успешно");
                }
            } else if (strcmp(cmd, "find") == 0) {
                int max = calc_ans(t);
			if(max ==0 )
				printf("Дерева нету\n");
			else
                printf("%d\n", max);
            } else if (strcmp(cmd, "exit") == 0) {
                v_destroy(v);
                free(v);
                free(str);
                clear_tree_recursive(t);
                break;
            } else if (strcmp(cmd, "help") == 0) {
                help_1();
            } else if (strcmp(cmd, "") == 0 || strcmp(cmd, "\n") == 0 || strcmp(cmd, "\t") == 0 ||
                       strcmp(cmd, " ") == 0) {
                continue;
            } else {
                h_command_is_not_found();
            }
            v_destroy(v);
            free(v);
            free(str);
        } else if (getline(&str, &buf_size, stdin) == -1) {
            free(str);
            clear_tree_recursive(t);
            break;
        }

    }
}