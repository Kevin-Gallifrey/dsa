#include <iostream>
using namespace std;

/*
    二分查找，对于顺序数组[lo,hi)，查找元素e，返回不大于e的最大的秩
    在比较时仅判断是否小于，使得两分支比较次数相同，达到平衡
    始终保证查找范围前部<=e，后部分>e
*/
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

/*
    fibonacci查找，使用三分支的比较(<>=)时，左右两侧的比较次数不同，
    为了达到平衡，应该使左侧深度更深，以此降低平均代价
    此时查找的mi取在黄金分割点
*/
class Fib
{
private:
    int g,k;    //g:上一个fib数，k:当前fib数
public:
    Fib(int);   //初始化为不小于n的最小Fibonacci项
    int get();
    int pre();
    int next();
};

Fib::Fib(int n)
{
    g=0;k=1;
    while (g < n)
        next();
}

int Fib::get()
{
    return k;
}

int Fib::next()
{
    k = g + k;
    g = k - g;
    return k;
}

int Fib::pre()
{
    g = k - g;
    k = k - g;
    return k;
}

int fibsearch(int* a, int lo, int hi, int e)
{
    Fib fib(hi-lo);
    int mi = lo + fib.pre() - 1;
    while (lo < hi)
    {
        if (a[mi] < e)
        {
            lo = mi + 1;
            fib.pre();
            mi = lo + fib.pre() - 1;
        }
        else if (e < a[mi])
        {
            hi = mi;
            mi = lo + fib.pre() - 1;
        }
        else
        {
            return mi;
        }
    }
    
    return -1;  //未找到
}

int main(int argc, char const *argv[])
{
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        a[i] = 2*i;
        cout << a[i] << '\t';
    }
    cout << endl;

    cout << binsearch(a,0,10,14) << endl;
    cout << fibsearch(a,0,10,14) << endl;

    return 0;
}
