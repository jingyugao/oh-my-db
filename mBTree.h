#include <array>
#include <iostream>

using namespace std;
namespace gjy {

//
//    template<class value_type, int N>
//    class BTree {
//    public:
//        BTree() {
//            root=create_node();
//            root->isLeaf= true;
//            root->used=0;
//        }
//
//        struct _node {
//            std::array<value_type, N - 1> _data;
//            std::array<_node *, N> _child;
//            size_t used;
//            bool isLeaf;
//            const value_type&operator[](size_t n)const {
//                return _data[n];
//            }
//            value_type &operator[](size_t n){
//                return _data[n];
//            }
//            friend class BTree;
//        };
//        _node* create_node(){
//            return new _node;
//        }
//        struct iterator{
//            _node*n;
//            size_t diff;
//        };
//
//        iterator insert(value_type x){
//
//
//        }
//
//        iterator insert_aux(_node*n,const value_type &x){
//
//        }
//        void split_child(_node*x,int i){
//            _node*y=x->_child[i];
//
//            _node *z=create_node();
//            z->isLeaf=y->isLeaf;
//
//
//        }
//        iterator find(value_type x) {
//
//            return find_aux(root,x);
//        }
//
//        iterator find_aux(_node* n,const value_type& x){
//            int i=0;
//            while (i<n->used&&n[i]<x){
//                i++;
//            }
//            if (i<n->used&&n[i]==x){
//                return iterator{n,i};
//            }
//            if(n->isLeaf)
//                return nullptr;
//            else
//                return find_aux(n->_child[i],x);
//        }
//
//
//
//        void *insert(_node *n, value_type x) {
//
//
//        }
//
//        _node *root;
//    };

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
    return new BTreeNode;
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
    //Dont mind iinsert mutli values
    void insert(int key, int val)
    {
        if (root == nullptr) {
            root = new BTreeNode;
            root->isLeaf = true;
            root->Keys[0] = key;
            root->use = 1;
            return;
        }

        insert_aux0(root,key,val);

        if(root->use=deg){
            fix_aux1(root);
        }
        else{
            root->use++;
        }


    }

    //simple insert
    int insert_aux0(BTreeNode *node, int key, int val)
    {
        int i = find_pos(node,key);

        for (int j = node->use - 1; j > i; j--) {
            node->Keys[j + 1] = node->Keys[j];
            node->Values[j+1]=node->Values[j];
        }
        node->Keys[i] = key;
        return i;
    }
//    int insert_with_child(BTreeNode *node, int k, int v, BTreeNode *child)
//    {
//        int i = 0;
//        while (i < node->use && k > node->Keys[i])
//            i++;
//        for (int j = use; j > i; j--) {
//            node->Keys[j] = node[j - 1];
//            node->Values[j] = node[j - 1];
//            node->Children[j + 1] = node->Children[j];
//        }
//        node->Keys[i] = k;
//        node->Values[i] = v;
//        node->Children[i] = child;
//        return i;
//    }

    //[.][q  w   e   r][.]       [.][q   c   w   e   r][.]
    //   /  /             -->       /   /   /
    // [*][abcde]                 [*][ab][de]
    //
    BTreeNode *split_node_to_parent(BTreeNode *node)
    {
        assert(node->use == deg + 1);
        int mid = deg / 2;
        BTreeNode *par = node->Parent;
        insert_aux0(node, node->Keys[mid], 0);
        node->use = deg / 2;

        BTreeNode *rightNode = createNode();
        rightNode->Parent = par;
        rightNode->use = deg - deg / 2;
        //std::copy
        for (int j = 0; j < rightNode->use; j++) {
            rightNode->Keys[j] = node->Keys[j + mid + 1];
        }
        if(par==nullptr) {
            par = createNode();
            par->use=0;
            root=par;
        }

        // insert to parent node
        int i = find_pos(par, node->Keys[mid]);
        for (int j = par->use; j > i; j--) {
            par->Children[j+1] = par->Children[j];
            par->Keys[j]=par->Keys[j-1];
            par->Values[j]=par->Values[j-1];
        }


        par->Children[i + 1] = rightNode;
        par->Children[i]=node;//left node
        par->use++;
        return par;
    }




    //node is full
    void fix_aux1(BTreeNode *node)
    {
        assert(node->use == deg);
        BTreeNode *n2=split_node_to_parent(node);

    };

private:
    BTreeNode *root;
}; // namespace gjy
} // namespace gjy
