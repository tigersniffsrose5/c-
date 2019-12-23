template <class T>
void InsertionSort(T a[],int n)
{
    int i,j;
    T t;
    for(i = 1;i < n;i++)
    {
        t = a[i];
        for(j = i - 1;j >= 0 && a[j] > t;j--)
            a[j+1] = a[j];
        a[j+1] = t;
    }
}
