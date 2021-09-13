#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#define Stack_size 10

class Stack
{
private:
    int a[Stack_size];
    int top;    // 栈顶指针
public:
    Stack();
    Stack(int*, int);
    void push(int);
    int pop();
    int read_top();
    bool isEmpty();
    bool isFull();
    bool isPermulation(Stack);
    void display();
};

Stack::Stack()
{
    top = -1;
}

Stack::Stack(int *e, int size)
{
    top = -1;
    if (size > Stack_size)
    {
        cout << "Too much elements.\n";
        size = Stack_size;
    }

    for (int i = 0; i < size; i++)
    {
        push(e[i]);
    }
}

bool Stack::isEmpty()
{
    return top >= 0 ? false : true;
}

bool Stack::isFull()
{
    return top < Stack_size - 1 ? false : true;
}

void Stack::push(int e)
{
    if (isFull())
    {
        cout << "Stack is full.\n";
        return;
    }

    a[++top] = e;
    return;
}

int Stack::pop()
{
    if (isEmpty())
    {
        cout << "Stack is empty.\n";
        return -1;
    }
    
    return a[top--];
}

int Stack::read_top()
{
    return a[top];
}

// 判断栈是否是栈x的栈混洗，利用模拟混洗过程
bool Stack::isPermulation(Stack x)
{
    int i = top;
    Stack s;    // 创建S栈，用于模拟混洗过程
    while (i > -1)
    {
        if (!s.isEmpty() && a[i] == s.read_top())
        {
            s.pop();
            i--;
        }
        else if (!x.isEmpty())
        {
            if (a[i] == x.read_top())
            {
                x.pop();
                i--;
            }
            else
                s.push(x.pop());
        }
        else
            return false;
    }
    return true;
}

void Stack::display()
{
    int temp = top;
    while (top > -1)
    {
        cout << read_top() << ' ';
        top--;
    }
    cout << endl;
    top = temp;
}

int main(int argc, char const *argv[])
{
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    //int b[10] = {0,1,9,8,7,6,5,4,3,2};
    int b[10] = {0,1,2,3,4,5,6,7,8,9};
    srand((unsigned)time(NULL));
    random_shuffle(b,b+10);

    Stack s1(a,10), s2(b,10);
    s1.display();
    s2.display();
    
    bool flag;
    flag = s2.isPermulation(s1);

    flag ? cout << "s2是s1的栈混洗\n" : cout << "s2不是s1的栈混洗\n";

    return 0;
}
