#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fly.h"

#define SIZE_OF_DATA_STRUCT 64

typedef struct {
    char name[64];
    int count;
    double avg;
} different_company;

void help() {
    fprintf(stderr, "Использование: ./<program_name> <file_name> <keys{-p, -f, -h}>\n");
    fprintf(stderr, "Ключ -p выводит задание варианта\nКлюч -f выводит таблицу\nКлюч -h выводит справку\n");
}

int find(different_company *arr, char *str) {
    for (int i = 0; i < SIZE_OF_DATA_STRUCT; i++) {
        char *s1 = arr[i].name;
        if (strcmp(s1, str) == 0) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int table = 0, work = 0;
    if (argc < 3) {
        fprintf(stderr, "Недостаточно аргументов\n");
        help();
        return 1;
    }
    for (int i = 2; i < argc; i++) {
        if (!strcmp(argv[i], "-f")) {
            table ++;
        } else if (!strcmp(argv[i], "-p")) {
            work ++;
        } else if (!strcmp(argv[i], "-h")) {
            help();
            return 0;
        }
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Что-то не так с файлом '%s'\n", argv[1]);
        return 1;
    }
    fly air;
    if (work) {
        double avg_delay = 0;
        int count = 0;
        while (fread(&air, sizeof(fly), 1, in) == 1) {
            avg_delay += air.delay;
            count++;
        }
        avg_delay /= count;
        printf("Средняя задержка рейсов всех авиакомпаний в минутах = %lf\n", avg_delay);
        fseek(in, 0, SEEK_SET);
        different_company *companies = malloc(SIZE_OF_DATA_STRUCT * sizeof(different_company));
        for (int i = 0; i < SIZE_OF_DATA_STRUCT; i++) {
            strcpy(companies[i].name, "");
        }
        int index = 0;
        while (fread(&air, sizeof(fly), 1, in) == 1) {
            int i = find(companies, air.company);
            if (i == -1) {
                strcpy(companies[index].name, air.company);
                companies[index].count = 1;
                companies[index].avg = air.delay;
                index++;
            } else {
                companies[i].count++;
                companies[i].avg += air.delay;
            }
        }
        printf("Количество авиакомпаний = %d\n", index);
        for (int i = 0; i < index; i++) {
            printf("%s	\n", companies[i].name);
        }
        for (int i = 0; i < index; i++) {
            double k = companies[i].avg / companies[i].count;
            if (k > avg_delay) {
                printf("Авиакомпания \"%s\" задерживает свои рейсы в среднем на %.2lf минут больше, чем другие\n",
                       companies[i].name, k - avg_delay);
            }
        }
    }
   fseek(in, 0, SEEK_SET);
   if (table) {
        while (fread(&air, sizeof(air), 1, in)) {
            fprintf(stdout,
                    "%d:%d:%s:%s:%d:%d\n", air.hour, air.minutes, air.company, air.city, air.terminal, air.delay);
        }
    }
    fclose(in);
}
