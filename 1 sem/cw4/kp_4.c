#include<stdio.h>
#include<math.h>
#include<stdbool.h>

typedef double(*Func)(double);
const double k = 10e9;

typedef struct {
	int iters;
	double root;
	bool success;
}result;

double mas_eps() {
	double epsilon, k=1;
	while(1+k != 1){
		epsilon = k;
		k /=2;
	}
	return epsilon;
}
double epsilon;

double dx(Func f, double x) {
	double eps = sqrt(epsilon);
	return (f(x+eps) - f(x - eps))/eps;
}
double ddx(Func f, double x) {
	double ddx = pow(epsilon, 0.25);
	return (f(x + 2*ddx) - 2 * f(x) + f(x - 2 *ddx)) / (4 * ddx * ddx);
}

result dht_method(Func f, double a, double b) {
	result r;
	r.root = (a + b) / 2;
	r.iters = 0;
	r.success = true;
	if (f(a) * f(b) > 0) {
		r.success = false;
		return r;
	}
	if (f(a) == 0){
		r.root = b;
		return r;
	} else if (f(b) == 0) {
		r.root = a;
		return r;
	}
	while (b - a > epsilon * k) {
		r.root = (a + b) / 2;
		r.iters += 1;
		if (f(a) * f(r.root) > 0.) a = r.root;
		else b = r.root;
	}
	r.root = (a + b) / 2;
	return r;
}

result iter_method(Func f, double a, double b){
	result r;
	r.iters = 0;
	r.success = true;
	r.root = (a+b)/2;
	double last = 0;
	if (fabs(dx(f, r.root - f(r.root)/dx(f, r.root))) < 1) {
		r.success = false;
		return r;
	}
	while(fabs(r.root - last) > epsilon * k) {
		r.iters +=1; 
		last = r.root;
		r.root = r.root - f(r.root)/dx(f, r.root);
		if (fabs(dx(f, r.root - f(r.root)/dx(f, r.root))) < 1) {
			r.success = false;
			return r;
		}
	}
	return r;
}
 
bool done(Func f, double x) {
	return (fabs(f(x) * ddx(f, x)) < dx(f, x) * dx(f, x));
}
result newton_method(Func f, double a, double b){
	result r;
	r.root = (a + b) / 2;
	r.iters = 0;
	r.success = true;
	double last = 0;
	if (!done(f, r.root)) {
		r.success = false;
		return r;
	}
	while(fabs(r.root - last) > epsilon * k){
		last = r.root;
		r.root = r.root - f(r.root)/dx(f, r.root);
		r.iters+=1;
		if(!done(f, r.root)) {
			r.success = false;
			return r;
		}
	}
	return r;
}

double a1 = 1.2, b1 = 2.0;
double func1(double x) {
	return x - 2 + sin(1/x);
}

double a2 = 3.0, b2 = 4.0;
double func2(double x){
	return exp(x) * log(x) - 10*x;
}


int main() {
	epsilon = mas_eps();
	result dht1, dht2, iter1, iter2, newt1, newt2;
	dht1 = dht_method(func1, a1, b1);
	dht2 = dht_method(func2, a2, b2);
	iter1 = iter_method(func1, a1, b1);
	iter2 = iter_method(func2, a2, b2);
	newt1 = newton_method(func1, a1, b1);
	newt2 = newton_method(func2, a2, b2);
	printf("for 28 variant:\n");
	if (dht1.success == true)
		printf("dichotomy method result for 28 func: iters = %d ans = %f \n", dht1.iters, dht1.root);
	if (iter1.success == true)
		printf("iteration method result for 28 func: iters = %d ans = %f \n", iter1.iters, iter1.root);
	if (newt1.success == true)
		printf("newton method result for 28 func: iters = %d ans = %f\n", newt1.iters, iter1.root);
	printf("\n"); 

	printf("for 1 variant:\n");
	if (dht2.success == true)
		printf("dichotomy method result for 1 func: iters = %d ans = %f \n", dht2.iters, dht2.root);
	if (iter2.success == true)
		printf("iteration method result for 1 func: iters = %d ans = %f \n", iter2.iters, iter2.root);
	if (newt2.success == true)
		printf("newton method result for 1 func: iters = %d ans = %f \n", newt2.iters, newt2.root);
}
