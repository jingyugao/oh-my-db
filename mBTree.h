#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#if 0
#define logLine(d) printf("%d %d\n", d, __LINE__)
#else
#define logLine(x) void(0);
#endif
using namespace std;
namespace omd {

template <class _Key,
          class _Tp,
          size_t deg = 4,
          class _Compare = std::less<_Key>>
//class _Alloc = std::allocator<std::pair<const _Key, _Tp>>>
class b_tree {

    //  struct inner_node;
    //   typedef inner_node node_type;

    //   struct node_base {
    //       bool isLeaf;
    //      unsigned short use;
    //      inner_node *Parent;
    //  };

    //  struct inner_node : public node_base {
    //      //typedef typename _Alloc::template rebind<inner_node>::other alloc_type;
    //      _Key Keys[deg + 1]; //last is sentiel
    //      inner_node * Children[deg + 2];
    //  };
    //struct leaf_node:public leaf_node{
    //    value_type Keys[deg+1];//last is sentiel
    //}

public:
    typedef _Key key_type;
    typedef _Tp data_type;
    typedef std::pair<key_type, data_type> value_type;
    typedef _Compare key_compare;

    struct node_type {
        bool isLeaf;
        int use;
        node_type *prev, *next; //left brother and right brother
        node_type *Parent;
        key_type Keys[deg + 1]; //last is sentiel
        node_type *Children[deg + 2];

        bool is_ok() { return use <= max_slot && use >= min_slot; }
        bool is_surplus() { return use > min_slot; };

        void insert(int i, std::pair<key_type, node_type *> val)
        {

            use++;
            Children[use] = Children[use - 1];
            for (int j = use - 1; j > i; j--) {
                Keys[j] = Keys[j - 1];
                Children[j] = Children[j - 1];
            }
            Keys[i] = val.first;
            Children[i] = val.second;
        }

        const key_type get_key(int i) const
        {
            assert(i < use);
            return Keys[i];
        }

        void set_key(int i, const key_type &k) { Keys[i] = k; }

        void insert_key(int i, const key_type &k)
        {

            use++;
            for (int j = use - 1; j > i; j--) {
                Keys[j] = Keys[j - 1];
            }
            Keys[i] = k;
        }
        void remove_key(int i)
        {
            for (int j = i; j < use - 1; j++) {
                Keys[i] = Keys[i + 1];
            }
            use--;
        }

        void set_child(int i, node_type *n) { Children[i] = n; }
        node_type *get_child(int i) const { return Children[i]; }

        void remove(int i)
        {
            for (int j = i; j < use - 1; j++) {
                Keys[i] = Keys[i + 1];
            }

            if (isLeaf) {
                for (int j = i; j < use; j++) {
                    Keys[i] = Keys[i + 1];
                }
            }

            use--;
        }

        size_t find_pos(const key_type &k)
        {
            assert(this != nullptr);
            size_t i = 0;
            while (i < use && k > Keys[i])
                i++;
            return i;
        }

        int find_child(node_type *child)
        {
            node_type *par = child->Parent;
            int i = 0;
            while (i < par->use + 1 && par->Children[i] != child)
                i++;
            return i /* <par->use+1?-1:i */;
        }
        node_type *get_child(int i)
        {
            assert(!isLeaf && i < use + 1);
            return Children[i];
        }

        key_type &first_key() const { return Keys[0]; }
        key_type &last_key() const { return Keys[use - 1]; }
        // key_type &first_key() { return Keys[0]; }
        // key_type &last_key() { return Keys[use - 1]; }

        node_type *first_child() const { return Children[0]; }
        node_type *last_child() const { return Children[use]; }
    };

    b_tree()
    {
        root = create_node();
        root->isLeaf = true;
    }
    void insert(const key_type &key, const data_type &val)
    {
        node_type *p = root;
        while (1) {
            size_t i = find_pos(p, key);

            if (p->isLeaf)
                break;
            p = p->Children[i];
        }

        insert_aux0(p, key, val);

        if (p->use == deg + 1) {
            fix(p);
        }
    }

    friend ostream &operator<<(ostream &out, const b_tree &bt)
    {
        std::queue<node_type *> q;

        node_type *p = nullptr;
        if (bt.root == nullptr)
            return out;
        q.push(bt.root);
        while (!q.empty()) {
            queue<node_type *> q2;
            while (!q.empty()) {

                p = q.front();
                q.pop();

                if (p->isLeaf)
                    cout << "<";
                else
                    cout << "[";
                for (int i = 0; i < p->use; i++) {
                    out << p->Keys[i] << " ";
                    if (!p->isLeaf)
                        q2.push(p->get_child(i));
                }
                if (p->isLeaf)
                    cout << ">";
                else
                    cout << "]";
                if (p->use != 0 && !p->isLeaf)
                    q2.push(p->last_child());
            }
            q = q2;
            out << endl;
        }

        return out;
    }

private:
    inline node_type *create_node()
    {
        node_type *p = new node_type;
        memset(p, 0, sizeof(node_type));
        return p;
    }

    //[.][q  w   e   r][.]       [.][q   c   w   e   r][.]
    //   /  /             -->       /   /   /
    // [*][abcde]                 [*][ab][de]
    //

    node_type *split_node_to_parent(node_type *node)
    {
        assert(node->use == deg + 1);
        size_t mid = deg / 2;
        node_type *par = node->Parent;
        if (par == nullptr) {
            par = create_node();
            par->isLeaf = false;
            par->use = 0;
            root = par;
        }

        node->use = deg / 2;
        node_type *rightNode = create_node();
        rightNode->isLeaf = node->isLeaf;
        rightNode->Parent = par;
        node->Parent = par;
        rightNode->use = deg - deg / 2;
        //std::copy
        for (int j = 0; j < rightNode->use; j++) {
            rightNode->Keys[j] = node->Keys[j + mid + 1];
        }
        if (!rightNode->isLeaf) {
            for (int j = 0; j < rightNode->use + 1; j++) {
                rightNode->Children[j] = node->Children[j + mid + 1];
                rightNode->Children[j]->Parent = rightNode;
            }
        }
        // insert to parent node
        size_t i = find_pos(par, node->Keys[mid]);
        // par->use++;
        // for (int j = par->use - 1; j > i; j--) {
        //     par->Children[j + 1] = par->Children[j];
        //     par->Keys[j] = par->Keys[j - 1];
        // }
        // par->Children[i + 1] = rightNode;
        // par->Children[i] = node; //left node
        // par->Keys[i] = node->Keys[mid];

        par->insert(i, make_pair(node->Keys[mid], node));
        par->set_child(i + 1, rightNode);
        rightNode->prev = node;
        node->next = rightNode;

        return par;
    }

    //node is full
    void fix(node_type *node)
    {
        assert(node->use == deg + 1);
        node_type *n2 = split_node_to_parent(node);
        if (n2->use == deg + 1)
            fix(n2);
    };
    //node is leaf and use<max_slot
    size_t insert_aux0(node_type *node, const key_type &k, const _Tp &v)
    {
        assert(node->isLeaf);
        size_t i = find_pos(node, k);
        logLine(i);
        logLine(k);
        logLine(node);
        node->insert_key(i, k);
        (void) v;
        return i;
    }

    inline size_t find_pos(node_type *node, key_type k)
    {
        assert(node != nullptr);
        size_t i = 0;
        while (i < node->use && k > node->Keys[i])
            i++;
        return i;
    }

    //simple iteator
    struct loc {
        node_type *node;
        size_t pos;

        void check() { assert(node && pos < node->use); }
    };
    loc find(const key_type &k)
    {
        node_type *p = root;
        while (p) {
            size_t i = find_pos(p, k);
            if (p->Keys[i] == k)
                return loc{p, i};
            if (p->isLeaf)
                return loc{nullptr, 0};
            p = p->Children[i];
        }
    }

    static const int min_slot = (deg - 1) / 2;
    static const int max_slot = deg;
    //i must in btree.
    void remove(const loc &i)
    {
        if (i->isLeaf)
            remove_in_leaf(i);
        else
            remove_in_inner(i);
    }

    //
    void remove_fix(const node_type &node)
    {
        assert(node->use < min_slot);
        node_type *par = node->Parent;
        int x = 0;
        while (x < par->use + 1 && par->Children[x] != node) {
            x++;
        }
        if (node->prev && node->prev->use > min_slot) {
            // reblance. borrow one from prev
            // index: x-1 x
            //      [p  a   ...]         [p   f   ...]
            //     / \ / \     -->    /  \ / \
            //   [.][lef][n]        [.] [le][a]
            //

            node_type *prev = node->prev;
            assert(par->Children[x] == node);
            assert(par->Children[x - 1] == prev);

            node->insert(
                0, std::make_pair(par->get_key(x - 1), prev->last_child()));
            par->set_key(x - 1, prev->last_key());
            prev->use--; //simple remove last key and child
            return;
        }

        // Symmetrically to prev
        // reblance. borrow one from prev
        // index: x  x+1
        //      [p  a   ...]         [p   r   ...]
        //     / \ / \     -->    /  \ / \
        //   [.][n][rig]        [.] [na][ig]
        //
        if (node->next && node->next->use > min_slot) {

            node_type *next = node->next;
            assert(par->Children[x] == node);
            assert(par->Children[x + 1] == next);
            node->insert_key(node->use, par->get_key(x));
            par->set_key(x, next->first_key());
            next->remove(0);
        }
        // no brother is surplus ,so merge
        if (node->prev) {
                       assert(node->prev->use == min_slot);
 
                        merge_child(node->prev,node);

            remove_fix(par);
        }

        if (node->next) {
            assert(node->next->use == min_slot);
            merge_child(node,node->next);
            remove_fix(par);
        }
        assert(0);
    }
    //       x-1 x
    //   [...  a   r]              [...   '  r]
    //        / \/ \         -->        /  \
    //      [p][n]                   [pan]
    void merge_child(node_type *prev, node_type *next)
    {
        assert(prev->next == next);
        assert(next->prev == prev);

        node_type *par = next->Parent;
        int x = 0;
        while (x < par->use + 1 && par->Children[x] != next) {
            x++;
        }
        assert(next->prev->use == min_slot);
        //(min_slot-1)+min_slot+1=2*min_slot<deg
        prev->use += next->use + 1;
        prev->Keys[min_slot] = par->Keys[x - 1];

        for (int j = 0; j < next->use; j++) {
            prev->Keys[j + min_slot] = next->Keys[j];
            prev->Children[1 + j + min_slot] = next->Children[j];
        }
    }

    // i->node is leaf
    // i->node->use is ok after remove i
    void remove_in_leaf(const loc &i)
    {

        assert(i->node->isLeaf);

        //the simplest remove
        i->node->remove(i->pos);
        if (i->node->is_ok()) {
            remove_fix(i->node);
        }
    }

    void remove_in_inner(const loc &i)
    {
        assert(!i->node->isLeaf);
        node_type *node = i->node;
        int p = i->pos;
        if (node_type *child = node->get_child(p)) {
            // remove o
            //      [n  o   d]          [n  i   d]
            //      / \/ \      -->     / \/ \      --> remove i in [chi]
            //    [][chi][]           [][chi][]
            //
            node->set_key(p, child->last_key());

            remove(loc{child, child->use - 1});
        }
        // if (node_type *child = node->get_child(p+1) && child->is_surplus()) {
        //     node->set_key(p,child->first_key());
        //     remove(loc{child,0});
        // }
    }

    // i->node->children[i->pos] is leaf and is ok
    void remove_aux21(const loc &i)
    {
        i.check();
        assert(!i->isLeaf);
        if (i->node->Children[i->pos]->use > min_slot) {
            assert(i->node->Children[i->pos]->isLeaf);
            node_type *child = i->node->Children[i->pos];
            i->node->Keys[i->pos] = child->last_key();
            child->use--;
        }
        if (i->node->Children[i->pos + 1]->use > min_slot) {
            assert(i->node->Children[i->pos + 1]->isLeaf);
            node_type *child = i->node->Children[i->pos + 1];
            i->node->Keys[i->pos] = child->first_key();
            i->node->remove(0);
            child->use--;
        }
        assert(0);
    }

    // i->node->children[i->pos] all not ok
    // merge children to one
    // min_slot*2<deg
    //[ p   a   r]             [p   '   r]
    //     / \ /   -->            /
    //  [le][ri]             [leari]
    void remove_aux3(const loc &i)
    {
        node_type *left_child = i->node->get_child(i->pos);
        node_type *right_child = i->node->get_child(i->pos + 1);
        assert(left_child->use == min_slot);

        assert(right_child->use == min_slot);
        //std::copy
        for (int j = 0; j < min_slot + 1; j++) {
            left_child->Keys[j + min_slot + 1] = right_child[j];
        }
        left_child->set_key(min_slot, i->node->Keys[i->pos]);
        left_child->set_child(min_slot, i->node->Children[i]);

        for (int j = i->pos; j < i->use; j++) {
            i->node->Keys[j] = i->node->Keys[j + 1];
            i->node->Children[j + 1] = i->node->Children[j + 2];
        }

        left_child->use = 2 * min_slot + 1;

        remove(loc{left_child, min_slot});
    }

    node_type *root;
};

// simple impleation in c
// struct BTreeNode {
//     int Keys[deg + 1];
//     int Values[deg + 1];
//     BTreeNode *Children[deg + 2];
//     BTreeNode *Parent;
//     bool isLeaf;
//     int use;
// };
// BTreeNode *createNode()
// {
//     BTreeNode *r = new BTreeNode;
//     memset(r, 0, sizeof(BTreeNode));
//     return r;
// };
// struct loc {
//     BTreeNode *node;
//     int offset;
// };

// loc bfind(BTreeNode *n, int k)
// {
//     int i = 0;
//     while (i < deg && k > n->Keys[i])
//         i++;

//     if (i < deg && k == n->Keys[i])
//         return loc{n, i};

//     if (n->isLeaf)
//         return loc{nullptr, 0};
//     return bfind(n->Children[i], k);
// }

// inline int find_pos(BTreeNode *node, int k)
// {
//     assert(node != nullptr);
//     int i = 0;
//     while (i < node->use && k > node->Keys[i])
//         i++;
//     return i;
// }
// class BTree {
// public:
//     BTree()
//     {
//         root = createNode();
//         root->use = 0;
//         root->isLeaf = true;
//     }
//     loc find(int k)
//     {
//         //        if (root == nullptr) {
//         //            return loc{nullptr, 0};
//         //        }
//         //
//         //        BTreeNode *p = root;
//         //
//         //        while (p) {
//         //
//         //            auto Ks = root->Keys;
//         //            int mid = Ks.size();
//         //            for (int i = 0; i < Ks.size(); i++) {
//         //                if (k < Ks[i]) {
//         //                    mid = i;
//         //                    break;
//         //                }
//         //            }
//         //            if (p->isLeaf){
//         //                return loc{p,mid};
//         //            }
//         //            p = p->Children[mid];
//         //        }
//         return loc{nullptr, 0};
//     }
//     //Dont mind insert mutli values
//     void insert(int key, int val)
//     {

//         BTreeNode *p = root;
//         while (1) {
//             int i = find_pos(p, key);

//             if (p->isLeaf)
//                 break;
//             p = p->Children[i];
//         }

//         insert_aux0(p, key, val);

//         if (p->use == deg + 1) {
//             fix(p);
//         }
//     }

//     //simple insert,node is leaf
//     int insert_aux0(BTreeNode *node, int key, int val)
//     {
//         int i = find_pos(node, key);

//         for (int j = node->use; j > i; j--) {
//             node->Keys[j] = node->Keys[j - 1];
//             node->Values[j] = node->Values[j - 1];
//         }
//         node->Keys[i] = key;
//         node->use++;
//         return i;
//     }

//     //[.][q  w   e   r][.]       [.][q   c   w   e   r][.]
//     //   /  /             -->       /   /   /
//     // [*][abcde]                 [*][ab][de]
//     //
//     BTreeNode *split_node_to_parent(BTreeNode *node)
//     {
//         assert(node->use == deg + 1);
//         int mid = deg / 2;
//         BTreeNode *par = node->Parent;
//         if (par == nullptr) {
//             par = createNode();
//             par->isLeaf = false;
//             par->use = 0;
//             root = par;
//         }
//         //insert_aux0(node, node->Keys[mid], 0);
//         node->use = deg / 2;

//         BTreeNode *rightNode = createNode();
//         rightNode->isLeaf = node->isLeaf;
//         rightNode->Parent = par;
//         node->Parent = par;
//         rightNode->use = deg - deg / 2;
//         //std::copy
//         for (int j = 0; j < rightNode->use; j++) {
//             rightNode->Keys[j] = node->Keys[j + mid + 1];
//             if (!rightNode->isLeaf) {
//                 rightNode->Children[j] = node->Children[j + mid + 1];
//                 rightNode->Children[j]->Parent = rightNode;
//             }
//         }
//         if (!rightNode->isLeaf) {
//             rightNode->Children[rightNode->use] = node->Children[deg + 1];
//             node->Children[deg + 1]->Parent = rightNode;
//         }
//         // insert to Parent node
//         int i = find_pos(par, node->Keys[mid]);
//         for (int j = par->use; j > i; j--) {

//             par->Children[j + 1] = par->Children[j];
//             par->Keys[j] = par->Keys[j - 1];
//             par->Values[j] = par->Values[j - 1];
//         }

//         par->Children[i + 1] = rightNode;
//         par->Children[i] = node; //left node
//         par->Keys[i] = node->Keys[mid];
//         par->use++;
//         return par;
//     }

//     //node is full
//     void fix(BTreeNode *node)
//     {
//         assert(node->use == deg + 1);
//         BTreeNode *n2 = split_node_to_parent(node);
//         if (n2->use == deg + 1)
//             fix(n2);
//     };
//     void print()
//     {

//         logLine(-1);
//         std::queue<BTreeNode *> q;

//         BTreeNode *p = nullptr;
//         if (root == nullptr)
//             return;
//         q.push(root);
//         while (!q.empty()) {
//             queue<BTreeNode *> q2;
//             while (!q.empty()) {

//                 p = q.front();
//                 q.pop();

//                 logLine(0);
//                 if (p->isLeaf)
//                     printf("<");
//                 else
//                     printf("[");

//                 for (int i = 0; i < p->use; i++) {
//                     printf("%d ", p->Keys[i]);
//                     if (!p->isLeaf)
//                         q2.push(p->Children[i]);
//                 }
//                 if (p->isLeaf)
//                     printf(">\t");
//                 else
//                     printf("]\t");
//                 if (p->use != 0 && !p->isLeaf)
//                     q2.push(p->Children[p->use]);
//             }
//             q = q2;
//             printf("\n");
//             logLine(q.size());
//         }
//         logLine(-2);
//     }

// private:
//     BTreeNode *root;
// };
} // namespace omd
