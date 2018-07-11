#include <array>
#include <cassert>
#include <iostream>
#include <queue>
using namespace std;
namespace gjy {

enum {
    deg = 4,
};
struct BTreeNode {
    int Keys[deg + 1];
    int Values[deg + 1];
    BTreeNode *Children[deg + 2];
    BTreeNode *Parent;
    bool isLeaf;
    int use;
};
BTreeNode *createNode()
{
    BTreeNode *r = new BTreeNode;
    memset(r, 0, sizeof(BTreeNode));
    return r;
};
struct loc {
    BTreeNode *node;
    int offset;
};

loc bfind(BTreeNode *n, int k)
{
    int i = 0;
    while (i < deg && k > n->Keys[i])
        i++;

    if (i < deg && k == n->Keys[i])
        return loc{n, i};

    if (n->isLeaf)
        return loc{nullptr, 0};
    return bfind(n->Children[i], k);
}

inline int find_pos(BTreeNode *node, int k)
{
    assert(node != nullptr);
    int i = 0;
    while (i < node->use && k > node->Keys[i])
        i++;
    return i;
}
class BTree {
public:
    BTree()
    {
        root = createNode();
        root->use = 0;
        root->isLeaf=true;
    }
    loc find(int k)
    {
        //        if (root == nullptr) {
        //            return loc{nullptr, 0};
        //        }
        //
        //        BTreeNode *p = root;
        //
        //        while (p) {
        //
        //            auto Ks = root->Keys;
        //            int mid = Ks.size();
        //            for (int i = 0; i < Ks.size(); i++) {
        //                if (k < Ks[i]) {
        //                    mid = i;
        //                    break;
        //                }
        //            }
        //            if (p->isLeaf){
        //                return loc{p,mid};
        //            }
        //            p = p->Children[mid];
        //        }
    }
    //Dont mind insert mutli values
    void insert(int key, int val)
    {

        BTreeNode *p = root;
        while (1) {
            int i = find_pos(p, key);
            if (p->Children[i] == nullptr)
                break;
            p = p->Children[i];
        }

        insert_aux0(p, key, val);

        if (p->use == deg + 1) {
            fix_aux1(p);
        }
    }

    //simple insert,node is leaf
    int insert_aux0(BTreeNode *node, int key, int val)
    {
        int i = find_pos(node, key);

        for (int j = node->use; j > i; j--) {
            node->Keys[j + 1] = node->Keys[j];
            node->Values[j + 1] = node->Values[j];
        }
        node->Keys[i] = key;
        node->use++;
        return i;
    }

    //[.][q  w   e   r][.]       [.][q   c   w   e   r][.]
    //   /  /             -->       /   /   /
    // [*][abcde]                 [*][ab][de]
    //
    BTreeNode *split_node_to_parent(BTreeNode *node)
    {
        assert(node->use == deg + 1);
        int mid = deg / 2;
        BTreeNode *par = node->Parent;
        if (par == nullptr) {
            par = createNode();
            par->use = 0;
            root = par;
        }
        //insert_aux0(node, node->Keys[mid], 0);
        node->use = deg / 2;

        BTreeNode *rightNode = createNode();
        rightNode->Parent = par;
        node->Parent = par;
        rightNode->use = deg - deg / 2;
        //std::copy
        for (int j = 0; j < rightNode->use; j++) {
            rightNode->Keys[j] = node->Keys[j + mid + 1];
            if(!rightNode.isLeaf)
                rightNode->Children[j] = node->Children[j + mid + 1];
        }
        rightNode->Children[rightNode->use] = node->Children[deg];
        // insert to parent node
        int i = find_pos(par, node->Keys[mid]);
        for (int j = par->use; j > i; j--) {
            par->Children[j + 1] = par->Children[j];
            par->Keys[j] = par->Keys[j - 1];
            par->Values[j] = par->Values[j - 1];
        }

        par->Children[i + 1] = rightNode;
        par->Children[i] = node; //left node
        par->Keys[i] = node->Keys[mid];
        par->use++;
        return par;
    }

    //node is full
    void fix_aux1(BTreeNode *node)
    {
        assert(node->use == deg + 1);
        BTreeNode *n2 = split_node_to_parent(node);
        if (n2->use == deg + 1)
            fix_aux1(n2);
    };
 #if 1
#define logLine(d) printf("%d %d\n",d,__LINE__) 
#else
#define logLine() do{}while(0) 
#endif
    void print()
    {

        std::queue<BTreeNode *> q;

        BTreeNode *p = nullptr;
        if (root == nullptr)
            return;
        q.push(root);   
        while (!q.empty()) {
            queue<BTreeNode *> q2;
            while (!q.empty()) {

                p=q.front();
                q.pop();
                                logLine(0);

                logLine(p);
                logLine(0);
                printf("[");
                for (int i = 0; i < p->use; i++) {
                    printf("%d ", p->Keys[i]);
                    
                    q2.push(p->Children[i]);
                }
                printf("]\t");
                if(p->use!=0)
                    q2.push(p->Children[p->use]);
            }
            q=q2;
            logLine(q.size());
        }
    }

private:
    BTreeNode *root;
}; // namespace gjy
} // namespace gjy
