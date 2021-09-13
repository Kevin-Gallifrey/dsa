/*
    列车调度
    A为入口，B为出口，S为中转盲端。所有铁道均为单轨单向式，
    列车行驶的方向只能是从A到S，再从S到B。
    S的容量有限，同时驻留的车厢不得超过m节。
    
    输入
    第一行为两个整数n，m。
    第二行为以空格分隔的n个整数，保证为{1, 2, ..., n}的一个排列，
    表示待判断可行性的驶出序列{a1，a2，...，an}。

    输出
    若驶出序列可行，则输出操作序列，
    其中push表示车厢从A进入S，pop表示车厢从S进入B。
    若不可行，则输出No。
*/

#include <iostream>
#include <string>
using namespace std;

class Stack
{
private:
    int* _a;
    int _capacity;
    int _size;
public:
    Stack(int);
    ~Stack();
    bool isEmpty();
    bool isFull();
    void push(int);
    int pop();
    int top();
};

Stack::Stack(int c=100)
{
    _capacity = c;
    _a = new int[_capacity];
    _size = -1;
}

Stack::~Stack()
{
    delete []_a;
}

bool Stack::isEmpty()
{
    return _size < 0;
}

bool Stack::isFull()
{
    return _size >= _capacity - 1;
}

void Stack::push(int e)
{
    if (!isFull())
    {
        _size++;
        _a[_size] = e;
    }
    else
    {
        cout << "The stack is full.\n";
        return;
    }
}

int Stack::pop()
{
    if (!isEmpty())
    {
        int x = _a[_size];
        _size--;
        return x;
    }
    else
    {
        cout << "The stack is empty.\n";
        return -1;
    }
}

int Stack::top()
{
    return _size > -1 ? _a[_size] : -1;
}

int main(int argc, char const *argv[])
{
    int m, n;
    cin >> n >> m;

    Stack a(n), b(n), s(m);
    for (int i = n; i > 0; i--)
    {
        a.push(i);
    }
    
    int temp[n];
    for (int i = 0; i < n; i++)
    {
        cin >> temp[i];
    }

    for (int i = n-1; i > -1; i--)
    {
        b.push(temp[i]);
    }
    
    
    string str;
    while (!a.isEmpty())
    {   
        if (s.top() == b.top())
        {
            s.pop();
            b.pop();
            str += "pop\n";
        }
        else
        {
            s.push(a.pop());
            str += "push\n";
        }    
    }
    
    while (!s.isEmpty())
    {   
        if (s.top() == b.top())
        {
            s.pop();
            b.pop();
            str += "pop\n";
        }
        else break;
    }
    
    if (b.isEmpty())
    {
        cout << str;    
    }
    else cout << "No\n";
    
    return 0;
}
