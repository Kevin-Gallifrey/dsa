#include <iostream>
#include <string>
using namespace std;

// 最长公共子序列
// 动态规划，填写dp表
int LCS(string a, string b){
    int len_a = a.length();
    int len_b = b.length();
    int dp[len_a+1][len_b+1];

    for (int i = 0; i < len_a+1; i++)
        for (int j = 0; j < len_b+1; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (a[i-1] == b[j-1])
            {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
            
        }
        
    return dp[len_a][len_b];
}

int main()
{
    string a, b;
    int maxlen = 0;

    cin >> a >> b;
    maxlen = LCS(a, b);
    cout << maxlen << endl;
    return 0;
}