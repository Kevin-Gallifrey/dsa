#include <iostream>
using namespace std;

/*
    数组循环左移
    void shift1(int* a, int n, int k);
    a-数组, n-数组长度, k-左移位数
*/
// 法一：迭代法
int shiftk(int* a, int n, int s, int k)    //从a[s]开始，以k为间隔循环左移
{
    int i = s, j = (s + k) % n;
    int temp = a[s];                       //保存起始元素
    int mov = 0;                           //移动次数
    while (j != s)
    {
        a[i] = a[j];
        i = j;
        j = (j + k) % n;
        mov++;
    }
    a[i] = temp;
    mov++;
    return mov;
}

void shift1(int* a, int n, int k)
{
    if ( k < 1 ) return;
    int mov = 0, s = 0;
    while (mov < n)
    {
        mov += shiftk(a,n,s,k);
        s++;
    }
}

// 法二：倒置法
void reverse(int* a, int lo, int hi)
{
    int temp = 0;
    while (lo < hi)
    {
        temp = a[hi];
        a[hi] = a[lo];
        a[lo] = temp;
        lo++;
        hi--;
    }
}

void shift2(int* a, int n, int k)
{
    reverse(a,0,k-1);
    reverse(a,k,n-1);
    reverse(a,0,n-1);
}

//输出数组
void print(int* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << '\t';
    }
    cout << endl;
}

int main()
{
    int n = 10;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
        b[i] = i;
    }
    
    int k = 4;
    shift1(a,n,k);
    shift2(b,n,k);

    print(a,n);
    print(b,n);
    return 0;
}
