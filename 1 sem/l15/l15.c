#include<stdio.h>

int main() {
	int n;
	scanf("%d",&n);
	int a[n][n];
	int N = n;
	for (int i = 0; i != n; i++)
		for (int j = 0; j != n; j++)
			scanf("%d", &a[i][j]);
	puts("\n");
	for (int i = 0; i < N / 2; i++) {
		for (int j = i; j < N - i - 1; j++) {
			 int temp = a[i][j];
			 a[i][j] = a[j][N-1-i];
			 a[j][N - 1 - i] = a[N - 1 - i][N - 1 - j];
			 a[N - 1 - i][N - 1 - j] = a[N - 1 - j][i];
			 a[N - 1 - j][i] = temp;
		}
	}
	for (int i = 0; i != n; i++) {
		for (int j = 0; j != n; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}
