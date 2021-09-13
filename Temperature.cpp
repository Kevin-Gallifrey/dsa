/*
    查询气温并计算平均值
    根据指定矩形区域内的观测站的气温值计算出平均气温。

    输入
    第一行为两个整数：观察站总数n，所需查询的总次数m
    以下n行分别描述各观察站：位置坐标为整数(x, y)，该站所测得温度值为整数t
    再以下m行分别对应于各次查询操作，整数(x1, y1)和(x2, y2)分别表示其西南角和东北角

    输出
    共m行，各含1个整数，表示每次查询所得平均温度。
    若查询区域不含任何观测站，则输出0。

    #使用kd-tree
*/

#include <iostream>
using namespace std;

struct Temperature
{
    double temp;
    int count;
};

class Node
{
private:
    double temperature;
    int x;
    int y;    
public:
    Node* parent;
    Node* lChild;
    Node* rChild;
    Node();
    Node(double, int, int);
    void setNode(double t, int a, int b) { temperature = t; x = a; y = b; }
    int getPosition(int d) { return d == 1 ? x : y; }   // 根据维度返回坐标
    double getTemperature() { return temperature; }
};

Node::Node()
{
    temperature = 0;
    x = 0;
    y = 0;
    parent = NULL;
    lChild = NULL;
    rChild = NULL;
}

Node::Node(double t, int x, int y)
{
    temperature = t;
    x = x;
    y = y;
    parent = NULL;
    lChild = NULL;
    rChild = NULL;
}

Node* selectionSort(Node *a, int n, int d);
Temperature searchArea(Node* p, int d, int x1, int y1, int x2, int y2);
Node* createKDTree(Node* p, int n, int d);

class KDTree
{
private:
    Node* root;
public:
    KDTree(/* args */);
    void create(Node*, int, int);
    double calAverageTemp(int, int, int, int);
};

KDTree::KDTree(/* args */)
{
    root = NULL;
}

void KDTree::create(Node* p, int n, int d)
{
    root = createKDTree(p,n,d);
}

// 生成一棵KD树，数组p，大小n，比较维度d
Node* createKDTree(Node* p, int n, int d)
{
    p = selectionSort(p,n,d);
    Node* root = &p[n/2];
    if (n > 2)
    {
        root->lChild = createKDTree(p, n/2, d*(-1));
        root->rChild = createKDTree(&p[n/2+1], n-n/2-1, d*(-1));
        root->lChild->parent = root;
        root->rChild->parent = root;
    }
    else if (n == 2)
    {
        root->lChild = createKDTree(p, n/2, d*(-1));
        root->lChild->parent = root;
        root->rChild = NULL;
    }
    else if (n == 1)
    {
        root->lChild = NULL;
        root->rChild = NULL;
    }
    else 
        return NULL;

    return root;
}

// 返回平均值。
double KDTree::calAverageTemp(int x1, int y1, int x2, int y2)
{
    Temperature t;
    t = searchArea(root, 1, x1, y1, x2, y2);
    return t.count == 0 ? 0 : t.temp/t.count;
}

// 在(x1, y1)和(x2, y2)分别表示其西南角和东北角的矩形范围内，
// 查询气温，并返回气温总和和数量。
// p为KD-Tree根节点，d为当前比较维度。
Temperature searchArea(Node* p, int d, int x1, int y1, int x2, int y2)
{   
    Temperature t, t1;
    t.count = 0;
    t.temp = 0;
    if (p == NULL)
    {
        return t;
    }
    
    int x = p->getPosition(1);
    int y = p->getPosition(-1);
    if (d == 1)
    {
        if (x < x1)
        {
            t1 = searchArea(p->rChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
        }
        else if (x > x2)
        {
            t1 = searchArea(p->lChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
        }
        else
        {
            if (y >= y1 && y <= y2)
            {
                t.temp += p->getTemperature();
                t.count++;
            }
            
            t1 = searchArea(p->lChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
            t1 = searchArea(p->rChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
        }
    }
    else
    {
        if (y < y1)
        {
            t1 = searchArea(p->rChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
        }
        else if (y > y2)
        {
            t1 = searchArea(p->lChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
        }
        else
        {
            if (x >= x1 && x <= x2)
            {
                t.temp += p->getTemperature();
                t.count++;
            }
            
            t1 = searchArea(p->lChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
            t1 = searchArea(p->rChild, d*(-1), x1, y1, x2, y2);
            t.count += t1.count;
            t.temp += t1.temp;
        }
    }
    
    return t;
}

// 选择排序，数组a，大小n，比较维度d
Node* selectionSort(Node *a, int n, int d)
{
    int temp = 0;
    int max = 0;
    for (int i = n-1; i > 0; i--)
    {
        max = a[i].getPosition(d);
        temp = i;
        for (int j = 0; j < i; j++)
        {
            int x = a[j].getPosition(d);
            if (max < x)
            {
                max = x;
                temp = j;
            }
        }
        swap(a[i], a[temp]);     
    }
    return a;
}

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    Node station[n];
    double t;
    int x, y;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y >> t;
        station[i].setNode(t,x,y);
    }
    KDTree tree;
    tree.create(station, n, 1);

    int x1, y1, x2, y2;
    double average[m];
    for (int i = 0; i < m; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        average[i] = tree.calAverageTemp(x1, y1, x2, y2);
    }

    for (int i = 0; i < m; i++)
    {
        cout << average[i] << endl;
    }
    
    return 0;
}
