#include <iostream>
#include <time.h>
using namespace std;

/*
    冒泡排序算法，数组范围[lo,hi)，升序排序
    当数组中没有逆序对时，排序完成。
    用last指向最后一次交换的位置，其后面的元素已经有序，不用参与下一次扫描
*/
void bubblesort(int* a, int lo, int hi)
{
    int last = --hi;
    while (lo < hi)
    {
        last = lo;  //在扫描前先将last设为lo，若没有执行交换，则last的值就不会被更改
        for (int j = lo; j < hi; j++)
        {
            if (a[j] > a[j+1])
            {
                swap(a[j], a[j+1]);
                last = j;
            }
        }
        hi = last;
    }
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

    bubblesort(a,0,10);
    
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << '\t';
    }
    cout << endl;

    return 0;
}
