#include<stdio.h>
enum {maxn = 100};

int main() {
	int m[maxn][maxn];
	int dir [4] = {0, -1, 0, 1};
	int n;
	scanf("%d", &n);
	for (int i = 0; i!=n; ++i)
		for (int j = 0; j != n; ++j)
			scanf("%d", &m[i][j]);
	puts("");
	int l = n;
	int p = 0;
	int i = n-1, j = -1;
	while (l != 0) {
		for (int k = 0; k != l; ++k) {
			i += dir[p % 4];
			j += dir[(p+3) % 4];
			printf("%d ", m[i][j]);
		}
		++p;
		l -= p % 2;
	}
	putchar('\n');
}

