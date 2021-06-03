#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "list.h"
#include "list_it.h"

void help(){
    printf("команды:\n");
    printf("insert {float value} {index} - to add element in a list on <index> position\n");
    printf("\tpushf {float value} - to push front element to a list\n");
    printf("\tpushb {float value} - to push back element to a list\n");
    printf("delete {index} - to delete element from <index> position in a list\n");
    printf("\tpopf - to pop front element of a list\n");
    printf("\tpopb - to pop back element of a list\n");
    printf("print - to print a list\n");
    printf("task {unsigned  int value} - to delete <unsigned  int value> elements in a list\n");
    printf("help - for help\n");
    printf("exit - exit\n");
}


void strip_blank_back(char *str) { //убирает пробелы и \n в конце строки
    size_t str_len = strlen(str);
    while (isblank(str[str_len - 1]) || isspace(str[str_len - 1])) {
        str[str_len - 1] = '\0';
        str_len--;
    }
}

int main(){
    help();
    List l;
    list_create(&l);
    while (true) {
        printf(">>> ");
        char *str = NULL, *arg1 = NULL, *arg2 = NULL, *arg_invalid, *cmd;
        size_t buf_size = 0;
        if (getline(&str, &buf_size, stdin) > 0) {//считывание строки до \n, включая \n
            strip_blank_back(str);
            cmd = strtok(str, " "); // считываем аргументы введенной команды
            if (cmd != NULL) {
                arg1 = strtok(NULL, " ");
                arg2 = strtok(NULL, " ");
                arg_invalid = strtok(NULL, " ");
            } else {
                cmd = str;
            }
            // Сравниваем команды
            if (strcmp(cmd, "insert") == 0) {
                if (arg1 != NULL && arg2 != NULL) {
                    char *es;
                    float value = strtof(arg1, &arg_invalid);
                    int index = (int) strtol(arg2, &es, 10);
                    if (arg1 != arg_invalid && arg2 != es) {
                        if (index < 0 || index > list_size(&l)) {
                            puts("invalid index");
                        } else {
                            list_insert(&l, index, value);
                        }
                    } else puts("invalid index or value");
                } else puts("You forgot to provide an arguments");

            } else if (strcmp(cmd, "pushf") == 0) {
                if (arg1 != NULL){
                    float value = strtof(arg1, NULL);
                    if(arg1 != arg_invalid) {
                    list_push_front(&l, value);
                    } else puts("invalid argument");
                } else puts("You forgot to provide an argument");

            } else if (strcmp(cmd, "pushb") == 0) {
                if (arg1 != NULL){
                    float value = strtof(arg1, &arg_invalid);
                    if(arg1 != arg_invalid) {
                        list_push_back(&l, value);
                    } else puts("invalid argument");
                } else puts("You forgot to provide an argument");

            } else if (strcmp(cmd, "print") == 0) {
                list_print(&l);

            } else if (strcmp(cmd, "delete") == 0) {
                if (arg1 != NULL) {
                    int index = (int)strtol(arg1, &arg_invalid, 10);
                    if (arg1 != arg_invalid && index >= 0 && index < list_size(&l)) {
                        list_delete(&l, index);
                    } else puts("invalid index");
                } else puts("You forgot to provide an argument");
            } else if (strcmp(cmd, "popf") == 0){
                list_pop_front(&l);

            } else if (strcmp(cmd, "popb") == 0){
                list_pop_back(&l);

            } else if (strcmp(cmd, "size") == 0) {
                printf("list size = %d\n", list_size(&l));

            } else if (strcmp(cmd, "exit") == 0) {
                break;

            } else if (strcmp(cmd, "task") == 0) {
                if (arg1 != NULL) {
                    int k = (int)strtol(arg1, &arg_invalid, 10);
                    if (arg1 != arg_invalid && k >= 0 && k < list_size(&l)) {
                        list_delete_last_k_elements(&l, k);
                    } else puts("invalid k");
                } else puts("You forgot to provide an argument");

            } else if (strcmp(cmd, "help") == 0) {
                help();
            } else if (strcmp(cmd, "") == 0 || strcmp(cmd, "\n") == 0 || strcmp(cmd, "\t") == 0 ||
                       strcmp(cmd, " ") == 0) {
                continue;
            } else {
                puts("Нет такой команды");
            }
        } else if (getline(&str, &buf_size, stdin) == -1) { //ctrl D
            break;
        }
    }
    list_destroy(&l);
    return 0;
}