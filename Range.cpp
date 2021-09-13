#include <iostream>
using namespace std;

void merge(int*, int, int, int);
void mergeSort(int*, int, int);
int binsearch(int*, int, int, int);

int main(int argc, char const *argv[])
{
    int n,m;
    cout << "请输入点的总数n，查询的次数m" << endl;
    cin >> n >> m;
    while (n < 0 || n > 5e5)
    {
        cout << "n范围出错，请重新输入" << endl;
        cin >> n;
    }
    while (m < 0 || m > 5e5)
    {
        cout << "m范围出错，请重新输入" << endl;
        cin >> m;
    }
    
    int s[n];
    cout << "请输入" << n << "个点的坐标" << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }

    int a[m],b[m];
    cout << "请输入" << m << "次查询的左右边界[a,b]" << endl;
    for (int j = 0; j < m; j++)
    {
        cin >> a[j] >> b[j];
        while (a[j] < 0 || a[j] > 1e7 || b[j] < 0 || b[j] > 1e7) 
        {
            cout << "范围出错，请重新输入" << endl;
            cin >> a[j] >> b[j];
        }
        
        if (a[j] > b[j])
        {
            swap(a[j],b[j]);
        }
    }
    
    mergeSort(s,0,n);
    int head, tail, num;
    cout << "查询结果" << endl;
    for (int k = 0; k < m; k++)
    {
        head = binsearch(s,0,n,a[k]-1);
        tail = binsearch(s,0,n,b[k]);
        num = tail - head;
        cout << k+1 << '\t' << num << endl;
    }
    
    return 0;
}

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

void mergeSort(int* a ,int lo, int hi)
{
    if (hi - lo < 2)
        return;
    
    int mi = (lo + hi) / 2;
    mergeSort(a, lo, mi); mergeSort(a, mi, hi);
    merge(a, lo, mi, hi);
}

int binsearch(int* a, int lo, int hi, int e)
{
    int mi = (lo + hi)/2;
    while (lo < hi)
    {
        e < a[mi] ? hi = mi : lo = mi + 1;
        mi = (lo + hi)/2;
    }
    return --lo;
}