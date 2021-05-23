#include <stdio.h>
#include <stdlib.h>
#include "fly.h"

int main(int argc, char* argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Недостаточно аргументов\n");
		return 1;
	}
	FILE *in = fopen(argv[1], "r");
	if(in == NULL) {
		fprintf(stderr, "Что-то не так с файлом '%s'\n", argv[1]);
		return 1;
	}
	FILE *out = fopen(argv[2], "w");
	if(out == NULL) {
		fclose(in);
		fprintf(stderr, "Что-то не так с файлом '%s'\n", argv[2]);
		return 2;
	}
	fly air;

	while (fscanf(in, "%d:%d:%[^:]:%[^:]:%d:%d\n",&air.hour,&air.minutes,air.company,air.city,&air.terminal,&air.delay) == 6){
		if (fwrite(&air, sizeof(fly), 1, out) != 1) {
			fprintf(stderr, "Не удалось записать в файл, '%s'\n", argv[2]);
			return 2;
		}
	}

	if (ferror(in) || ferror(out)) {
		fprintf(stderr, "Неизвестная ошибка\n");
		return 2;
	}
	fclose(in);
	fclose(out);
	return 0;
}	
