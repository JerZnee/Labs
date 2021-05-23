#include <stdio.h>

int ki(int *a, int *b);
int rec(int *a, int *b) {
	while ((*a) >= 0) {
		if ((*a) > 100 && (*b) < 0) {
			(*a)=(*a)/2;
			(*b)+=10;
			ki(a, b);
		} else {
			(*a)-=20;
			(*b)-=32;
			ki (a, b);
		}
	 } return (*b)*(*a)+1;
}
int ki(int *a, int *b) { 
	if ((*b) > 0) (*b)*=-1;  
	while ((*b) <= 0)  {
		(*b)+=31;
		rec(a, b);
		return (*a)*(*b)/7;	
	} return (*b)+20%(*a)+3;
}
int main() { 
	int a, b, c , d=0;
	scanf ("%d%d%d", &a, &b, &c);
	b=ki(&a, &b);
	for (int i=0; i<c;i++) { 
	
		d=3+a*c;
	}
	printf ("a=%d\nb=%d\nc=%d\nd=%d\n",a,b,c,d);
	
}
