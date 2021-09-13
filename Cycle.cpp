/*
    所谓循环移位是指一个字符串的首字母移到末尾, 其他字符的次序保持不变。
    比如ABCD经过一次循环移位后变成BCDA。
    给定两个字符串，判断它们是不是可以通过若干次循环移位得到彼此。
    
    输入
    第一行为一个整数m。
    下面m行，每行包含两个由大写字母'A'~'Z'组成的字符串，中间由空格隔开。

    输出
    对于每行输入，输出这两个字符串是否可以通过循环移位得到彼此：YES表示是，NO表示否。

    # 串匹配
*/

#include <iostream>
#include <string>
using namespace std;

// 串匹配 KMP算法
void match(string, string);

int main(int argc, char const *argv[])
{
    int m;
    cin >> m;
    string t[m], p[m];
    for (int k = 0; k < m; k++)
    {
        cin >> t[k] >> p[k];
    }

    for (int k = 0; k < m; k++)
    {
        if (t[k].length() != p[k].length())
        {
            cout << "NO\n";
        }
        else
        {
            t[k] = t[k] + t[k];
            match(t[k], p[k]);
        }
    }
    return 0;
}

void match(string t, string p)
{
    // 构建next[]表
    int next[p.length()] = {-1};
    int i = 0, j = next[0];
    while (i < p.length() - 1)
    {
        if (j < 0 || p[i] == p[j])
        {
            i++;
            j++;
            next[i] = (p[i] != p[j] ? j : next[j]);
        }
        else
            j = next[j];
    }
    
    // 匹配
    i = 0;  // 文本串指针
    j = 0;  // 模式串指针
    int m = p.length();
    int n = t.length();
    while (j < m && i < n)
    {
        if (j < 0 || p[j] == t[i])
        {
            j++;
            i++;
        }
        else
            j = next[j];
    }

    if (i - j > t.length() - p.length())
        cout << "NO\n";
    else
        cout << "YES\n";   
}