#include <iostream>
#include <queue>
#include <vector>

struct CBinTreeNode
{
    CBinTreeNode(int v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    CBinTreeNode* nodes[2];
    int value;
};

class CBinTree
{
public:
    CBinTree();
    void Print();
    bool Insert(int x);
    bool Remove(int x);
private:
    bool Find(int x, CBinTreeNode**& p);
    CBinTreeNode** Rep(CBinTreeNode** p);
    void InOrder(CBinTreeNode* n);
    void Levels(CBinTreeNode* n);
    CBinTreeNode* root;
};

CBinTree::CBinTree()
{   
    root = 0;
}

bool CBinTree::Find(int x, CBinTreeNode**& p)
{
    for ( p = &root; *p && (*p)->value != x;
         p = &((*p)->nodes[ x > (*p)->value ]) );
    return *p != 0;
}

bool CBinTree::Insert(int x)
{
    CBinTreeNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinTreeNode(x);
    return 1;
}
    
void CBinTree::InOrder(CBinTreeNode* n)
{
    if ( !n ) return;
    InOrder( n->nodes[0] );
    std::cout<<n->value<<" ";
    InOrder( n->nodes[1] );
}

void CBinTree::Levels(CBinTreeNode* n)
{
    if (!n) return;
    std::queue<std::pair<CBinTreeNode*,int>> q;
    q.push({n,0});
    int l = 0;
    while( !q.empty() )
    {
        int last = l;
        std::pair<CBinTreeNode*,int> pp = q.front();
        CBinTreeNode* nn = pp.first;
        l = pp.second;
        if ( nn->nodes[0] )  q.push({nn->nodes[0],l+1});
        if ( nn->nodes[1] )  q.push({nn->nodes[1],l+1});
        if ( last != l )    std::cout<<"\n";
        std::cout<<nn->value<<"("<<l<<") ";
        q.pop();
    }
}

void CBinTree::Print()
{
    Levels(root);
    std::cout<<"\n";
}

void VecInsertRec(CBinTree* t, int* v, int start, int end)
{
    if (start > end)
        return;

    int mid = start + (end - start) / 2;
    t->Insert(v[mid]);
    VecInsertRec(t, v, start, mid - 1);
    VecInsertRec(t, v, mid + 1, end);
}

int main()
{
    CBinTree t;
    int v[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int size = sizeof(v) / sizeof(v[0]);

    // Asegúrate de que el array esté ordenado antes de llamar a la función recursiva
    VecInsertRec(&t, v, 0, size - 1);

    t.Print();
}
