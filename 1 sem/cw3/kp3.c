#include <math.h>
#include <stdio.h>

typedef  double ld;


const int max_iters = 100000;

ld compute_epsilon() {
	ld eps = 1;
	while (1 + eps != 1)
		eps /= 2;
	return eps;
}
ld inner_func(ld x) {
	return -1 * log(2*fabs(sin(x/2)));
}


ld teilor_member(ld x, int n) {
	ld v = 0;
	v += cos(x*n)/n;
	return v;
}


int main() {
	ld pi = acos(-1); 
	ld k = 10e7;
	ld a = pi / 5;
	ld b = 6 * pi / 5;
	int steps;
	scanf("%d" ,&steps);
	ld step = (b - a) / steps;
	ld del = 0;
	ld x = a;
	printf("Machine epsilon for long double for this system is %.16f\n", compute_epsilon());
	printf("______________________________________________________________________________\n");
	printf("|  x   |        Sum        |        Del`ta      |    -ln(sin(x))     |   n   |\n");
	printf("|______|___________________|____________________|____________________|_______|\n");
	for (ld i = 0; i <= steps; i ++) {
		int n = 1;
		ld cur_member = 1;
		ld sum = 0;
		ld prev = 0;
		while ((fabs(cur_member - prev) > compute_epsilon() * k && n < max_iters) || n < 50) {
			prev = cur_member;
			cur_member = teilor_member(x, n);
			sum += cur_member;
			n++;
		}
		del = fabs(sum - inner_func(x));
		printf("| %.2f | %.15f | %.15f | %.15f | %4d |\n", x, sum, del, inner_func(x), n);
		if (i != b) x += step;
		else x = b;
	}
	printf("|______|____________________|___________________|____________________|_______|\n");
}



