template <class T>
void BubbleSort(T a[],int n)
{
    int i,j,k;
    T t;
    for(i = n - 1; i > 0;i = k)
        //将 i 设置为被交换的最后一对元素中较小的下标
        for(k = j = 0; j < i;j++)
            if(a[j] > a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
                k = j; //如有交换发生,记录较小元素的下标
            }
}
