#include <iostream>
using namespace std;

struct LightHouse
{
    int x,y;
};

void sortAsX(LightHouse*, int, int);
void display(LightHouse*, int, int);
int invNumBetween(LightHouse*, int, int, int);  //计算前后两段之间的逆序对数
int invNumY(LightHouse*, int, int);             //计算数组中逆序对数

int main(int argc, char const *argv[])
{
    int n;
    cout << "请输入灯塔总数n" << endl;
    cin >> n;

    LightHouse t[n];
    for (int i = 0; i < n; i++)
    {
        cout << "请输入灯塔的横、纵坐标\n";
        cin >> t[i].x >> t[i].y;
    }
    sortAsX(t,0,n);
    display(t,0,n);

    int invNum;
    invNum = invNumY(t,0,n);
    cout << "能相互照亮的灯塔对共" << n*(n-1)/2 - invNum << "对\n";

    return 0;
}

void sortAsX(LightHouse *a , int lo, int hi)
{
    int last = --hi;
    LightHouse temp;
    while (lo < hi)
    {
        last = lo;  //在扫描前先将last设为lo，若没有执行交换，则last的值就不会被更改
        for (int j = lo; j < hi; j++)
        {
            if (a[j].x > a[j+1].x)
            {
                swap(a[j], a[j+1]);
                last = j;
            }
        }
        hi = last;
    }
}

void display(LightHouse *a, int lo, int hi)
{
    for (int i = lo; i < hi; i++)
    {
        cout << a[i].x << '\t' << a[i].y << endl;
    }
}

/* 
    采用分而治之的策略。
    套用归并排序的方法，将序列分成前后两段，
    分别计算其中的逆序对数，再计算二者之间的逆序对数
*/
int invNumY(LightHouse *a, int lo, int hi)
{
    if (hi - lo < 2)
    {
        return 0;
    }
    int mi = (lo + hi) / 2;
    return invNumY(a,lo,mi) + invNumY(a,mi,hi) + invNumBetween(a,lo,mi,hi);
}

int invNumBetween(LightHouse *a, int lo, int mi, int hi)
{
    int lb = mi -lo;
    int lc = hi - mi;
    LightHouse b[lb];
    for (int i = 0; i < lb; i++)
    {
        b[i] = a[lo + i];
    }
    int j = 0, k = mi ,l = lo;
    int invNum = 0;
    while (j < lb)
    {
        if (k < hi && a[k].y < b[j].y)
        {
            a[l] = a[k];
            k++; l++;
            invNum += lb - j;
        }
        else
        {
            a[l] = b[j];
            j++; l++;
        }    
    }
    
    return invNum;
}