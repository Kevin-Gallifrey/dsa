#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    输入两个字符串s1和s2，以及初始光标位置p
    在s1中移动光标位置去依次寻找s2中的字符
    光标可连续移动，移动到最右边再向右移就到最左边，最左边向左移到最右边
    要求移动最少的次数，找到s2中全部的字符
*/

/*
    用于寻找字符，返回找到的字符的位置
    由于可能有多个位置，用vector进行存储
*/
vector<int> findchar(char, string);

/*
    计算最少的移动次数
    由于可能有重复的字符出现，需要考虑光标移动到哪一个字符处
    列出所有匹配的字符的位置，需要找到一条从头到尾代价最短的路径
    使用viterbi算法，对于每一个节点，保留一条代价最短的进入路径。
*/
int minCost(vector<int>*, int, int, int);


int main(int argc, char const *argv[])
{
    string s1, s2;
    cin >> s1 >> s2;
    int p;
    cin >> p;
    int s1len = s1.length();
    int s2len = s2.length();
    vector<int> position[s2len];
    for (int i = 0; i < s2len; i++)
    {
        position[i] = findchar(s2[i], s1);
    }
    
    int c;
    c = minCost(position, s2len, p, s1len);
    cout << c << endl;
    return 0;
}

vector<int> findchar(char c, string s)
{
    vector<int> pos;
    for (int i = 0; i < s.length(); i++)
    {
        if (c == s[i])
        {
            pos.push_back(i);
        }
    }
    return pos;
}

int minCost(vector<int>* pos, int s2len, int p, int s1len)
{
    vector<int> costmin[s2len];
    int cost;
    int s;

    for (int j = 0; j < pos[0].size(); j++)
    {
        s = abs(pos[0][j] - p);
        if (s > s1len - s)
            s = s1len - s; 
        costmin[0].push_back(s);
    }
    
    
    for (int i = 1; i < s2len; i++)
    {
        for (int j = 0; j < pos[i].size(); j++)
        {
            s = abs(pos[i][j] - pos[i-1][0]);
            if (s > s1len - s)
                s = s1len - s; 
            cost = s + costmin[i-1][0];
            for (int k = 1; k < pos[i-1].size(); k++)
            {
                s = abs(pos[i][j] - pos[i-1][k]);
                if (s > s1len - s)
                    s = s1len - s; 
                if (cost > s + costmin[i-1][k])
                    cost = s + costmin[i-1][k];    
            }
            costmin[i].push_back(cost);
        }
    }
    
    int tmp = costmin[s2len-1][0];
    for (int i = 1; i < costmin[s2len-1].size(); i++)
    {
        if (tmp > costmin[s2len-1][i])
            tmp = costmin[s2len-1][i];
    }
    return tmp;
}