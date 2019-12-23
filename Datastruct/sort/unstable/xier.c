#include<stdio.h>

int main ()
{
    int a[100], i, j, t, n, k;
    scanf("%d", &n);

    for ( i = 0; i < n; i++ ) {
        scanf("%d", &a[i]);
    }

    k = n/2;
    while ( k > 0 ) {
        for ( i = k; i < n; i++ ) {
            t = a[i];
            for ( j = i-k; j >= 0 && a[j] > t; j-=k ) {
                a[j+k] = a[j];
            }
            a[j+k] = t;
        }
        k = k/2;
    }

    for ( i = 0; i < n; i++ ) {
        printf("%d  ", a[i]);
    }

    return 0;

}


