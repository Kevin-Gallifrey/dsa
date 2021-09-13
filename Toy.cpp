/*
    一个4*2的魔方玩具，可以进行以下三种变换
    A 交换上下两行。比如，图(a)经此变换后结果如图(b)所示。
    B 循环右移。比如，图(b)经此变换后结果如图(c)所示。
    C 中心顺时针旋转。比如，图(c)经此变换后结果如图(d)所示。

    1 2 3 4     8 7 6 5     5 8 7 6     5 1 8 6
    8 7 6 5     1 2 3 4     4 1 2 3     4 2 7 3
     图(a)       图(b)       图(c)       图(d)

    输入
    第一行是一个正整数，即你拥有的魔方玩具总数N。
    接下来共N行，每行8个正整数，是1~8的排列，表示该玩具的当前状态。
    这里，魔方状态的表示规则为：前四个数自左向右给出魔方的第一行，
    后四个数自右向左给出第二行。比如，初始状态表示为“1 2 3 4 5 6 7 8”。

    输出
    共N行，各含一个整数，依次对应于复原各玩具所需执行变换的最少次数。
    特别地，若某个玩具不可复原，则相应行输出-1。

    # 目前输出的是从初始状态到该状态的变换次数，不是复原的次数。
    # e.g. 循环右移3次，复原仅需一次。
*/

#include <iostream>
using namespace std;

struct Node
{
    int data[8];
    Node* suc;
    Node* pre;
};

class Queue
{
private:
    Node* header;
    Node* trailer;
    int _size;
public:
    Queue();
    ~Queue();
    void enqueue(int*);
    void dequeue(int*);
    bool isEmpty() { return _size <= 0; }
};

Queue::Queue()
{
    header = new Node;
    trailer = new Node;
    header->suc = trailer;
    header->pre = NULL;
    trailer->suc = NULL;
    trailer->pre = header;
    _size = 0;
}

Queue::~Queue()
{
    int a[8];
    while (_size > 0)
        dequeue(a);
    delete header;
    delete trailer;   
}

void Queue::enqueue(int *a)
{
    Node *q = new Node;
    for (int i = 0; i < 8; i++)
    {
        q->data[i] = a[i];
    }    
    q->suc = trailer;
    q->pre = trailer->pre;
    trailer->pre->suc = q;
    trailer->pre = q;
    _size++;
}

void Queue::dequeue(int *temp)
{
    Node *p = header->suc;
    header->suc = p->suc;
    p->suc->pre = header;
    for (int i = 0; i < 8; i++)
    {
        temp[i] = p->data[i];
    }
    delete p;
    _size--;
}

class Toy
{
private:
    int hashTable[40320];   //总状态数 8!=40320
public:
    Toy(/* args */);
    int hash(int*);
    void swapLines(int*, int*);
    void shiftRight(int*, int*);
    void rotate(int*, int*);
    void createTable();
    int search(int*);
};

Toy::Toy(/* args */)
{
    for (int i = 0; i < 40320; i++)
    {
        hashTable[i] = -1;
    }
}

// 将全排列数组映射到n!的空间内
int Toy::hash(int *a)
{
    int key = 0, tmp = 0;
    for (int i = 0; i < 7; i++)
    {
        tmp = 0;
        for (int j = i + 1; j < 8; j++)
        {
            if (a[j] < a[i])
                tmp++;    
        }
        key += tmp; 
        key *= (7-i);
    }
    return key;
}

void Toy::swapLines(int *a, int *b)
{
    for (int i = 0; i < 4; i++)
    {
        b[i] = a[7 - i];
        b[7 - i] = a[i];
    }
}

void Toy::shiftRight(int *a, int *b)
{
    b[0] = a[3];
    for (int i = 1; i < 4; i++)
    {
        b[i] = a[i-1];
    }
    for (int i = 4; i < 7; i++)
    {
        b[i] = a[i+1];
    }
    b[7] = a[4];
}

void Toy::rotate(int *a, int *b)
{
    b[0] = a[0];
    b[1] = a[6];
    b[2] = a[1];
    b[3] = a[3];
    b[4] = a[4];
    b[5] = a[2];
    b[6] = a[5];
    b[7] = a[7];
}

void Toy::createTable()
{
    Queue queue;
    int root[8] = {1,2,3,4,5,6,7,8};
    int step = 0, key = hash(root);
    hashTable[key] = step;
    queue.enqueue(root);

    int temp[8];
    int next1[8], next2[8], next3[8];
    while (!queue.isEmpty())
    {
        queue.dequeue(temp);
        step = hashTable[hash(temp)];

        swapLines(temp, next1);
        key = hash(next1);
        if (hashTable[key] == -1 || hashTable[key] > step)
        {
            hashTable[key] = step + 1;
            queue.enqueue(next1);
        }
        
        shiftRight(temp, next2);
        key = hash(next2);
        if (hashTable[key] == -1 || hashTable[key] > step)
        {
            hashTable[key] = step + 1;
            queue.enqueue(next2);
        }

        rotate(temp, next3);
        key = hash(next3);
        if (hashTable[key] == -1 || hashTable[key] > step)
        {
            hashTable[key] = step + 1;
            queue.enqueue(next3);
        }
    }
}

int Toy::search(int *a)
{
    int key = hash(a);
    return hashTable[key];
}

int main(int argc, char const *argv[])
{
    Toy toy;
    toy.createTable();
    int n;
    cin >> n;
    int a[8], b[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> a[j];
        }
        b[i] = toy.search(a);
    }
    
    for (int i = 0; i < n; i++)
    {
        cout << b[i] << endl;
    }
    
    return 0;
}
