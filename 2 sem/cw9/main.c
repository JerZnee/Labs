#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "array.h"
#include <time.h>



void prompt(){
    printf("> ");
}


void usage(){
    puts("Справка:");
    puts("\th - вывести справку");
    puts("\to <KEY_FILENAME> <DATA_FILENAME> - open files with specified names");
    puts("\tr - развернуть массив");
    puts("\ts - сортировать");
    puts("\tm - перемешать массив");
    puts("\tp [NUMBER] - print array(or specified element of array)");
    puts("\tb <VALUE> - binary search in array");
    puts("\tf - очистить массив");
    puts("\tq - звершить программу");
}

void parse_filenames(string keys, string data){
    char buf = (char)getchar();
    while(buf == ' ') buf = (char)getchar(); // skip whitespaces

    size_t i = 0, j = 0;

    bool is_key = true;

    while(buf != '\n' && buf != EOF){
        if(buf == ' '){
            is_key = false;
            buf = (char)getchar();
            continue;
        }
        if(is_key) keys[i++] = buf;
        else data[j++] = buf;

        buf = (char)getchar();
    }
}

int count_newlines(FILE *file){
    char buf = 'a';
    int cnt = 0;
    while(!feof(file) && buf != EOF){
        buf = (char)fgetc(file);
        if(buf == '\n') cnt++;
    }
    fseek(file, 0, SEEK_SET);
    return cnt;
}

array* read_arr(){
    string fnkeys = calloc(256, sizeof(char)), fndata = calloc(256, sizeof(char));
    parse_filenames(fnkeys, fndata);
    if(fnkeys == NULL || fndata == NULL){
        return NULL;
    }
    FILE* fkeys = fopen(fnkeys, "r"), *fdata = fopen(fndata, "r");
    free(fnkeys);free(fndata);
    if(fkeys == NULL || fdata == NULL)
        return NULL;

    int nlines1 = count_newlines(fkeys);
    int nlines2 = count_newlines(fdata);
    if(nlines1 != nlines2)
        return NULL;

    int_8* keys = calloc(nlines1, sizeof(int_8));
    string* data = calloc(nlines1, sizeof(string));

    for (size_t i = 0; i < nlines1; ++i) {
        string line = NULL, ptr = NULL;
        size_t size_line;

        if(getline(&line, &size_line, fkeys) == -1){
            return NULL;
        }
        keys[i] = strtoul(line, &ptr, 10);

        if(getline(data + i, &size_line, fdata) == -1){
            return NULL;
        }
    }
    return array_create(keys, data, nlines1);
}

size_t bin_search(array* arr, int_8 value){
    int l = -1, r = arr->len;
    int m;

    while(r-l > 1){
        m = (l+r) / 2;
        if(arr->array[m].key > value){
            r = m;
        }else if(arr->array[m].key < value){
            l = m;
        } else{
            l = m;
            break;
        }
    }
    return l;
}

int main(){
    srandom(time((NULL)));  // псевдорандом, принимающий время

    array *arr = NULL;
    bool sorted = false;

    char cmd;

    while (true){
        prompt();
        cmd = (char)getchar();
        while(cmd == ' ' || cmd == '\n') cmd = (char)getchar(); // skip whitespaces

        if(cmd == 'q')break;
        if(cmd == 'h'){
            usage();
            continue;
        }
        if(arr == NULL && cmd != 'o'){
            puts("Неверный ключ, попробуйте еще раз");
            usage();
            continue;
        }

        string sbuf, ssbuf;
        size_t ibuf;
        size_t index;
        switch (cmd) {
            case 'o':
                arr = read_arr();
                sorted = false;
                if(arr == NULL){
                    puts("Неправильное имя или формат файла");
                }
                break;
            case 'p':
                getline(&sbuf, &ibuf, stdin);
                index = strtoul(sbuf, &ssbuf, 10);
                if(sbuf != ssbuf && index < arr->len && index >= 0){
                    printf("%s\n", arr->array[index].data);
                }else {
                    array_print(arr);
                }
                break;
            case 'b':
                if(!sorted){
                    puts("Массив не отсортирован");
                    continue;
                }
                getline(&sbuf, &ibuf, stdin);
                index = strtoul(sbuf, &ssbuf, 10);
                if(sbuf == ssbuf){
                    puts("Неправильный индекс");
                }else{
                    int bs = bin_search(arr, index);
                    if(bs == -1){
                        puts("Ключ не найден");
                    }else{
                        printf("%s\n", arr->array[bs].data);
                    }
                }
                break;
            case 'f':
                array_free(arr);
                arr = NULL;
                sorted = false;
                break;
            case 'r':
                array_reverse(arr);
                sorted = false;
                break;
            case 's':
                array_quick_sort(arr);
                sorted = true;
                break;
            case 'm':
                array_shuffle(arr);
                sorted = false;
                break;
            default:
                usage();
                continue;
        }
    }

    if(arr != NULL)
        array_free(arr);

}


