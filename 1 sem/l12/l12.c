#include <stdio.h>

long long  prog(long long n) {
	long long k = 0, N, ans, j, s;
		N = n;
		ans =0;
		s = 1;
		k = 0;
		while (n > 0 || n < 0) {
			k++;	
			n /= 10;
		}	      
		n = N;
		j = k;
		if (k == 1 || k == 0) {
			return  n;
		} else if (k == 2) {
			return 0;
		} else if (k == 3) {
			ans = (ans + n / 100) * 10 ;
			n = n  % 10;
			ans +=n;
			return  ans;
		} else if (k > 3) {
			for (int i = 0; i < k-1; i++) {
				s*=10;
			}			
			while (k > 0) {
				if (k != 2 && k != j-1) {
					ans*=10;
					ans += (n / s);
					n%= s;
					k--;
					s/=10;
				} else {
					n%=s;
					k--;
					s/=10;
				}
			}
			return ans;
		}
	return 0;
}


int main () {
	long long n;
	while (scanf("%lld", &n) != EOF) {
		printf ("%lld\n",prog(n));
	}
}
