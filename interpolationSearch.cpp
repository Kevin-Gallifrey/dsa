#include <iostream>
using namespace std;

/*
    插值查找，有序向量中如果各元素独立且均匀随机分布，那么各元素大致呈现线性增长趋势
    有(mi-lo)/(hi-lo) = (e-a[lo])/(a[hi]-a[lo])
    通过猜测mi提高收敛速度
    输入向量[lo,hi), 返回不大于e的最大的秩
*/
int interpolationSearch(int* a, int lo, int hi, int e)
{
    int mi;
    while (lo < hi)
    {
        hi - lo == 1 ? mi = lo : mi = lo + (hi-1-lo)*(e-a[lo])/(a[hi-1]-a[lo]);
        e < a[mi] ? hi = mi : lo = mi +1;
    }
    return --lo;  //未找到
}

int main(int argc, char const *argv[])
{
    int a[10];
    for (int i = 0; i < 10; i++)
    {
        a[i] = i * i;
        cout << a[i] << '\t';
    }
    cout << endl;

    int j;
    for (int i = 0; i < 10; i++)
    {
        j = i * i + 1;
        cout << interpolationSearch(a,0,10,j) << '\t';
    }
    cout << endl;

    return 0;
}
