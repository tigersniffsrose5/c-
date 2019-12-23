#include<stdio.h>
#include <limits.h>

int a[100], L[100], R[100];

void Merge ( int a[], int p, int q, int r )
{
    int n1, n2, i, j, k;
    n1 = q-p+1;
    n2 = r-q;
    for ( i = 1; i <= n1; i++ )
        L[i] = a[p+i-1];
    for ( j = 1; j <= n2; j++ )
        R[j] = a[q+j];
    L[n1+1] = INT_MAX;
    R[n2+1] = INT_MAX;
    i = 1;
    j = 1;
    for ( k = p; k <= r; k++ ) {
        if ( L[i] <= R[j] ) {
            a[k] = L[i++];
        }
        else {
            a[k] = R[j++];
        }
    }
}

void mergesort ( int a[], int p, int r )
{
    int q;
    if ( p < r ) {
        q = (p+r)/2;                  //分解待排序的n个元素的序列成具n/2个元素的子序列
        mergesort(a, p, q);           //使用归并排序递归地排序两个子序列
        mergesort(a, q+1, r);
        Merge(a, p, q, r);           //合并两个已排序的子序列以产生已排序的答案
    }
    else
        return;
}

int main (void)
{
    int n, i;
    scanf("%d", &n);

    for ( i = 1; i <= n; i++ ) {
        scanf("%d", &a[i]);
    }

    mergesort(a, 1, n);

    for ( i = 1; i <= n; i++ ) {
        printf("%d  ", a[i]);
    }

    return 0;
}

