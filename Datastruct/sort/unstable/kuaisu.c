#include<stdio.h>

int a[101];

void swap ( int x, int y )
{
    int t;
    t = a[x];
    a[x] = a[y];
    a[y] = t;
    return;
}

int partition ( int a[], int p, int r )
{
    int i, j;
    i = p-1;
    for ( j = p; j <= r-1; j++ ) {
        if ( a[j] <= a[r] ) {
            i++;
            swap(i, j);
        }
    }
    swap(i+1, r);
    return i+1;
}

int random_partition ( int a[], int p, int r )
{
    int i;
    i = rand() % (r - p + 1) + p;              //随机选择数组中一个数和最后一个交换，这样保证啊a[r]是等概率地从子数组中选取的
    swap(r, i);
    return partition(a, p, r);
}

void random_quicksort ( int a[], int p, int r )
{
    int q;
    if ( p < r ) {
        q = random_partition(a, p, r);          //将问题分为几个子问题
        random_quicksort(a, p, q-1);           //运用递归法调用自己实现分治
        random_quicksort(a, q+1, r);
    }
}

int main (void)
{
    int n, i;
    scanf("%d", &n);

    for ( i = 1; i <= n; i++ ) {
        scanf("%d", &a[i]);
    }

    random_quicksort(a, 1, n);

    for ( i = 1; i <= n; i++ ) {
        printf("%d  ", a[i]);
    }

    return 0;

}

