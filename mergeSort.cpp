#include <iostream>
#include <ctime>
using namespace std;

/*
    二路归并，将两个有序序列合成一个有序序列
*/
void merge(int* a, int lo, int mi, int hi)
{
    int i = 0, j = mi, k = lo;
    int lb = mi - lo;
    int b[lb];
    for (int m = 0; m < lb; m++)
    {
        b[m] = a[lo+m];
    }
    
    while (i < lb)
    {
        if (!(j < hi) || b[i] < a[j])
            a[k++] = b[i++];
        else
            a[k++] = a[j++];
    }
    
}

/*
    归并排序，数组范围[lo,hi)，升序排序
    序列一分为二；子序列递归排序；合并有序子序列
*/
void mergeSort(int* a ,int lo, int hi)
{
    if (hi - lo < 2)
        return;
    
    int mi = (lo + hi) / 2;
    mergeSort(a, lo, mi); mergeSort(a, mi, hi);
    merge(a, lo, mi, hi);
}

int main(int argc, char const *argv[])
{
    int a[10];
    srand((unsigned)time(NULL)); 
    for (int i = 0; i < 10; i++)
    {
        a[i] = rand() % 100;
        cout << a[i] << '\t';
    }
    cout << endl;

    mergeSort(a,0,10);
    
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << '\t';
    }
    cout << endl;

    return 0;
}
