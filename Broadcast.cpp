/*
    n个小镇，每个小镇都要安装一台发射机并播放各自的节目。
    不过，只有两个波段可用，而使用同一波段的发射机会互相干扰。
    已知每台发射机的信号覆盖范围是以它为圆心，20km为半径的圆形区域。
    因此，如果距离小于20km的两个小镇使用同样的波段，那么它们就会由于波段干扰而无法正常收听节目。
    现在给出这些距离小于20km的小镇列表，试判断整个地区的居民能否正常听到广播节目。
    
    输入
    第一行为两个整数n，m，分别为小镇的个数以及接下来小于20km的小镇对的数目。
    接下来的m行，每行2个整数，表示两个小镇的距离小于20km（编号从1开始）。

    输出
    如果能够满足要求，输出1，否则输出-1。
*/

#include <iostream>
using namespace std;

enum Status {visited, discovered, undiscovered};

class Town
{
private:
    int freq;
    int* neighbors;
    int num;
    Status status;
public:
    Town();
    ~Town();
    void initNeigbors(int);
    void addNeighbors(int);
    int getNeighbors(int i) { return neighbors[i]; }
    Status getStatus() { return status; }
    void setStatus(Status s) { status = s; }
    int getNum() { return num; }
    void setFreq(int f) { freq = f; }
    int getFreq() { return freq; }
};

Town::Town()
{
    freq = 0;
    neighbors = NULL;
    num = 0;
    status = undiscovered;
}

Town::~Town()
{
    delete []neighbors;
}

void Town::initNeigbors(int m)
{
    neighbors = new int[m];
}

void Town::addNeighbors(int n)
{
    neighbors[num] = n;
    num++;
}

struct Node
{
    int data;
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
    void enqueue(int);
    int dequeue();
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
    while (_size > 0)
        dequeue();
    delete header;
    delete trailer;   
}

void Queue::enqueue(int a)
{
    Node *q = new Node;
    q->data = a;
    q->suc = trailer;
    q->pre = trailer->pre;
    trailer->pre->suc = q;
    trailer->pre = q;
    _size++;
}

int Queue::dequeue()
{
    Node *p = header->suc;
    header->suc = p->suc;
    p->suc->pre = header;
    int temp = p->data;
    delete p;
    _size--;
    return temp;
}

// 广度优先搜索，t[n]为顶点，返回1表示没有冲突，-1表示有冲突
int bfs(Town* t, int n)
{
    if (t[n].getStatus() == visited)
    {
        return 1;
    }
    
    Queue queue;
    t[n].setStatus(discovered);
    t[n].setFreq(1);
    queue.enqueue(n);

    int m, f, j;
    while (!queue.isEmpty())
    {
        m = queue.dequeue();
        f = t[m].getFreq();
        for (int i = 0; i < t[m].getNum(); i++)
        {
            j = t[m].getNeighbors(i);
            if (t[j].getStatus() == visited)
            {
                continue;
            }
            else if (t[j].getStatus() == discovered)
            {
                if (t[j].getFreq() == f)
                {
                    return -1;
                }
                else continue;    
            }
            else
            {
                t[j].setFreq(f*(-1));
                t[j].setStatus(discovered);
                queue.enqueue(j);
            }
        }
        t[m].setStatus(visited);
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    int n,m;
    cin >> n >> m;
    Town towns[n];
    for (int i = 0; i < n; i++)
    {
        towns[i].initNeigbors(m);
    }

    int t1, t2;
    for (int i = 0; i < m; i++)
    {
        cin >> t1 >> t2;
        towns[t1-1].addNeighbors(t2-1);
        towns[t2-1].addNeighbors(t1-1);
    }
    
    int result;
    for (int i = 0; i < n; i++)
    {
        result = bfs(towns, i);
        if (result == -1) break;
    }
    
    cout << result << endl;
    return 0;
}
