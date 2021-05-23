#include <stdio.h>
#include <stdbool.h>
bool sep(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == EOF;
}

bool num(char c) {
	return c == '0' || c == '1' || c == '2';
}

typedef enum {
	LOOKING_NUM,
	FIND_NUM,
	BAD_SIGN
} state_t;

int main() {
	int n = 0;
	int c;
	state_t state = LOOKING_NUM;
	int c_last = 0, o = 0;
	do  {
		c = getchar();
		if (state == LOOKING_NUM) {
			if (num(c)) {
				state = FIND_NUM;
				n = c - '0';
			} else if (c == '-') {
				state = FIND_NUM;
				o = 1;
			} else if (!sep(c) && !num(c)) {
				state = BAD_SIGN;
				o = 0;
			}
		} else if (state == FIND_NUM) {
			if (sep(c)) {
				state = LOOKING_NUM;
				if (c_last == '0') {
					if (o == 0) {
						printf("%d\n", n);
						n=0;
				} else if (o == 1) {
					printf("-%d\n", n);
					n = 0;
					o=0;
				}
			}
			} else if (!num(c)) {
				state = BAD_SIGN;
				o=0;
			} else {
				n *= 10;
				n += c - '0';
			}
		} else {
			if (sep(c)) {
				state = LOOKING_NUM;
			}
		}
		c_last = c;
	} while (c !=EOF);

}
