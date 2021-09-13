/*
    找出清单中重复的提名

    输入
    第1行为1个整数n，表示提名清单的长度。以下n行各为一项提名。

    输出
    所有出现重复的提名（多次重复的仅输出一次），
    且以其在原清单中首次出现重复（即第二次出现）的位置为序。

    # 使用散列
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Bucket
{
private:
    string s;
    bool duplicate;
public:
    Bucket();
    void insert(string);
    bool isEmpty() { return s.empty(); }
    bool isEqual(string s1) { return s == s1; }
    bool isDuplicate() { return duplicate; }
    void setDuplicate() { duplicate = true; }
};

Bucket::Bucket()
{
    s = "";
    duplicate = false;
}

void Bucket::insert(string str)
{
    s = str;
    duplicate = false;
}

// 将字符串转为整型
int string2int(string s)
{
    int x = 0;
    for (int i = 0; i < s.length(); i++)
    {
        x += (s[i] - 'a' + 1) * pow(2,i);
    }
    return x;
}

int main(int argc, char const *argv[])
{
    int tableSize = 6001;
    Bucket hashTable[tableSize];
    int n;
    string str;
    cin >> n;

    int addr, j = 0, offset = 0;
    string duplicatedName;
    for (int i = 0; i < n; i++)
    {
        cin >> str;
        addr = string2int(str) % tableSize;
        while (j < tableSize)
        {
            if (hashTable[addr + offset].isEmpty())
            {
                hashTable[addr + offset].insert(str);
                break;
            }
            else if (hashTable[addr + offset].isEqual(str))
            {
                if (!hashTable[addr + offset].isDuplicate())
                {
                    duplicatedName += (str + '\n');
                    hashTable[addr + offset].setDuplicate();
                }
                break;
            }
            
            j++;
            offset = (j * j) % tableSize;
        }
    }
    
    cout << duplicatedName;
    return 0;
}
