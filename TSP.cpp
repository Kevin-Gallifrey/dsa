/*
    旅行商
    选定一个村庄A作为起点，依次经过尽可能多的村庄，路途中的每个村庄都经过仅一次，最终到达终点村庄B。
    
    输入
    第一行包括两个整数n，m，分别表示村庄的个数以及可以通行的道路的数目。
    以下共m行，每行用两个整数v1和v2表示一条道路，
    两个整数分别为道路连接的村庄号，道路的方向为从v1至v2，n个村庄编号为[1, n]。
    输入保证道路之间没有形成环

    输出
    输出一个数字，表示符合条件的最长道路经过的村庄数。
*/

#include <iostream>
using namespace std;

enum Status {visited, discovered, undiscovered};

class Village
{
private:
    int* roads;
    enum Status status;
    int neighbors;  //与其相邻的邻居数
    int depth;      //从其出发最多可以到达的村庄的个数
public:
    Village(int);
    Village();
    ~Village();
    void initRoads(int);
    void addRoad(int);
    int getRoad(int i) { return roads[i]; }
    enum Status getStatus() { return status; }
    void setStatus(Status s) { status = s; }
    int getNeighbors() { return neighbors; }
    int getDepth() { return depth; }
    void setDepth(int d) { depth = d; }
};

Village::Village(int n)
{
    roads = new int[n];
    status = undiscovered;
    neighbors = 0;
    depth = 0;
}

Village::Village()
{
    roads = NULL;
    status = undiscovered;
    neighbors = 0;
    depth = 0;
}

Village::~Village()
{
    delete []roads;
}

void Village::initRoads(int m)
{
    roads = new int[m];
}

void Village::addRoad(int a)
{
    roads[neighbors] = a;
    neighbors++;
}

// 深度优先搜索，v[n]为顶点，返回depth值
int dfs(Village *v, int n)
{
    int temp, d = 0;
    v[n].setStatus(discovered);
    for (int i = 0; i < v[n].getNeighbors(); i++)
    {
        temp = v[n].getRoad(i);
        if (v[temp].getStatus() == visited)
        {
            d = max(d, v[temp].getDepth() + 1);
        }
        else if (v[temp].getStatus() == discovered)
        {
            cout << "Discover a loop.\n";
        }
        else  // v[temp].getStatus() == undiscovered
        {
            d = max(d, dfs(v, temp) + 1);
        }
    }
    v[n].setStatus(visited);
    v[n].setDepth(d);
    return d;
}

int main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    Village villages[n];
    for (int i = 0; i < n; i++)
    {
        villages[i].initRoads(m);
    }

    int v1, v2;
    for (int i = 0; i < m; i++)
    {
        cin >> v1 >> v2;
        villages[v1-1].addRoad(v2-1);
    }
    
    int maxDepth = 0;
    for (int i = 0; i < n; i++)
    {
        if (villages[i].getStatus() == undiscovered)
        {
            maxDepth = max(maxDepth, dfs(villages, i));
        }   
    }

    cout << maxDepth + 1 << endl;
    return 0;
}
