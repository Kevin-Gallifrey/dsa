/*
    某计算集群同一时刻只有单个任务处于执行状态。
    初始状态下，每个任务都由称作优先级数的一个整数指定优先级，该数值越小优先级越高；
    若优先级数相等，则任务名ASCII字典顺序低者优先。
    此后，CPU等资源总是被优先级数最小的任务占用；
    每一任务计算完毕，再选取优先级数最小下一任务。
    不过，这里的任务在计算结束后通常并不立即退出，
    而是将优先级数加倍（加倍计算所需的时间可以忽略）并继续参与调度；
    只有在优先级数不小于 2^32 时，才真正退出。
    根据初始优先级设置，按照上述调度原则，预测一批计算任务的执行序列。

    输入
    第一行为以空格分隔的两个整数n和m，n为初始时的任务总数，
    m为所预测的任务执行序列长度，每行末尾有一个换行符。
    以下n行分别包含一个整数和一个由不超过8个小写字母和数字组成的字符串。
    前者为任务的初始优先级数，后者为任务名。数字和字符串之间以空格分隔。

    输出
    最多m行，各含一个字符串。按执行次序分别给出执行序列中前m个任务的名称，
    若执行序列少于m，那么输出调度器的任务处理完毕前的所有任务即可。

    # 优先级队列
*/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Task
{
public:
    string name;
    int priority;
    Task(/* args */);
    void setTask(string s, int n) { name = s; priority = n; }
    void setTask(Task t) { name = t.name; priority = t.priority; }
    bool operator<(const Task&);
};

Task::Task(/* args */)
{
}

bool Task::operator<(const Task& t)
{
    if (this->priority == t.priority)
    {
        return this->name < t.name;
    }
    else return this->priority < t.priority;
    
}

class PQ
{
private:
    Task *tasks;
    int size;
public:
    PQ(int);
    ~PQ();
    int ProperParent(int);
    void percolateUp(int);      // 上滤
    void percolateDown(int);    // 下滤
    void init(Task*, int);      // 装入任务，批量建堆
    string run();               // 运行一次任务
};

PQ::PQ(int n)
{
    tasks = new Task[n];
    size = n;
}

PQ::~PQ()
{
    delete []tasks;
}

// 在i和其孩子中选择正确的父亲
int PQ::ProperParent(int i)
{
    if ((i+1) * 2 < size)   // 左右孩子都在存在
    {
        if (tasks[i*2+1] < tasks[(i+1)*2] && tasks[i*2+1] < tasks[i])
            return i*2 + 1;
        if (tasks[(i+1)*2] < tasks[i*2+1] && tasks[(i+1)*2] < tasks[i])
            return (i+1) * 2;
        else
            return i;
    }
    else if (i*2 + 1 < size)    // 只有左孩子
    {
        if (tasks[i*2+1] < tasks[i])
            return i*2 + 1;
        else
            return i;
    }
    else                    // 没有孩子
        return i;   
}

void PQ::percolateDown(int i)
{
    int j;
    j = ProperParent(i);
    while (i != j)
    {
        swap(tasks[i], tasks[j]);
        i = j;
        j = ProperParent(i);
    }
}

void PQ::percolateUp(int i)
{
    int j = (i-1) / 2;
    while (tasks[i] < tasks[j])
    {
        swap(tasks[i], tasks[j]);
        i = j;
        j = (i-1) / 2;
    }
}

void PQ::init(Task *t, int n)
{
    for (int i = 0; i < n; i++)
        tasks[i].setTask(t[i]);
    
    for (int i = n/2-1; i > -1; i--)
        percolateDown(i);
}

string PQ::run()
{
    if (size <= 0)
    {
        return NULL;
    }
    
    string name = tasks[0].name;
    tasks[0].priority *= 2;
    int pri = tasks[0].priority;
    swap(tasks[0], tasks[size - 1]);
    
    // 首元素下滤
    size--;     // 先排除末元素
    percolateDown(0);

    // 末元素上滤
    if (pri < pow(2,32))
    {
        size++;     // 加入末元素（刚刚执行的任务）
        percolateUp(size - 1);
    }
    
    return name;
}

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    Task t[n];
    int pri;
    string name;
    for (int i = 0; i < n; i++)
    {
        cin >> pri >> name;
        t[i].setTask(name, pri);
    }

    PQ CPU(n);
    CPU.init(t, n);
    string finished;
    for (int i = 0; i < m; i++)
    {
        finished = CPU.run();
        if (finished.empty())
            break;
        
        cout << finished << endl;
    }

    return 0;
}
