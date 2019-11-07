#include<stdio.h>

int a[101], b[101], c[101];

int main (void)
{
	int n, i, j, k;
	scanf("%d %d", &n, &k);  // n为个数，k为最大的数

	for ( i = 1; i <= n; i++ ) {
		scanf("%d", &a[i]);
	}
	
	for ( j = 1; j <= n; j++ ) {
		c[a[j]] = c[a[j]]+1;
	}

	for ( i = 1; i <= k; i++ ) {
		c[i] = c[i]+c[i-1];
	}

	for ( j = n; j >= 1; j-- ) {
		b[c[a[j]]] = a[j];
		c[a[j]] = c[a[j]]-1;
	}

	for ( i = 1; i <= n; i++ ) {
		printf("%d  ", b[i]);
	}

	return 0;
}
