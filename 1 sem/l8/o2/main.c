#include "pro.h"
#include <stdio.h>

int main(void) {
	int a, f
	scanf ("%d", &a);
	for (int i=0; i < a; i++) {
		if (a >= 0) {
			 f=pro(a ,2);
		} else {
			f=pro(2, a);
		}
	
	}
	printf("f=%d\n", f);
}
