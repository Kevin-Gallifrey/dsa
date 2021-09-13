#include <iostream>
#include <string>
using namespace std;

int eliminate(string&, int);

int main(int argc, char const *argv[])
{
    string s;
    int n;
    cout << "请输入初始序列" << endl;
    cin >> s;
    cout << "请输入操作次数" << endl;
    cin >> n;

    int k;
    string t;
    for (int i = 0; i < n; i++)
    {
        cout << "操作" << i << ": \n";
        cin >> k >> t;
        s.insert(k,t);
        while (k >= 0)
        {
            k = eliminate(s,k);
        }
        cout << "当前序列: \n";
        if (s.length() > 0)
        {
            cout << s << endl;
        }
        else cout << '-' << endl;
    }
    
    return 0;
}

int eliminate(string& s, int k)
{
    int lo = k, hi = k;
    int len = s.length();

    while (hi < len && s[hi] == s[k])
    {
        hi++;
    }
    while (lo > -1 && s[lo] == s[k])
    {
        lo--;
    }
    if (hi - lo > 3)
    {
        lo++;
        s.erase(lo, hi - lo);
        return lo > 0 ? --lo : 0;
    }
    else
    {
        return -1;
    }
    
}