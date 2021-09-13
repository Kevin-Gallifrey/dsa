/*
    真二叉树重构
    对于“真二叉树”（每个内部节点都有两个孩子的二叉树），
    给定它的先序、后序遍历序列足以完全确定它的结构。

    输入
    第一行为一个整数n，即二叉树中节点的个数。
    第二、三行为已知的先序、后序遍历序列。

    输出
    仅一行，给定真二叉树的中序遍历序列。
*/
#include <iostream>
using namespace std;

struct Node
{
    int e;
    Node* succ;
};

class List
{
private:
    Node* header;
    Node* last;
public:
    List(/* args */);
    ~List();
    void remove(int);
    void insertAsLast(int);
    int first();
};

List::List(/* args */)
{
    header = new Node;
    header->succ = NULL;
    last = header;
}

List::~List()
{
    Node* p;
    while (header->succ)
    {
        p = header->succ;
        header->succ = p->succ;
        delete p;
    }
    delete header;
    
}

void List::remove(int a)
{
    Node* p = header;
    Node* q = p->succ;
    while (q)
    {
        if (q->e == a)
        {
            if (q == last)
                last = p;
            p->succ = q->succ;
            delete q;
        }
        else 
            p = q;
        
        q = p->succ;
    }
}

void List::insertAsLast(int a)
{
    Node* p = new Node;
    p->e = a;
    p->succ = NULL;
    last->succ = p;
    last = p;
}

int List::first()
{
    return header->succ ? header->succ->e : -1;
}

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int pre[n];
    for (int i = 0; i < n; i++)
    {
        cin >> pre[i];
    }

    List post;
    int temp;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        post.insertAsLast(temp);
    }
    
    int inorder[n], stack[n];
    int p = 0;  //inorder中的位置指针
    int q = -1; //stack中top指针

    for (int i = 0; i < n; i++)
    {
        if (pre[i] == post.first())
        {
            temp = pre[i];
            inorder[p++] = temp;
            post.remove(temp);
            if (q > -1)
            {
                temp = stack[q--];
                inorder[p++] = temp;
                post.remove(temp);   
            }
        }
        else
        {
            stack[++q] = pre[i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << inorder[i] << ' ';
    }
    cout << endl;
    
    return 0;
}
