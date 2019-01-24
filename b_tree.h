#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#if 1
#define logLine(d) printf("%d %d %s\n", d, __LINE__, __FUNCTION__)
#else
#define logLine(x) void(0);
#endif
using namespace std;
namespace omd
{

template <class _Key, class _Tp, /* int len,*/ int deg = 4, class _Compare = std::less<_Key>>
//class _Alloc = std::allocator<std::pair<const _Key, _Tp>>>
class BTree
{

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

    static const int min_slot = (deg - 1) / 2;
    static const int max_slot = deg;

    struct node_type
    {
        bool isLeaf;
        int use;
        node_type *prev, *next; //left brother and right brother
        node_type *Parent;
        key_type Keys[deg + 1]; //last is sentiel
        data_type Datas[deg];
        node_type *Children[deg + 2];
        int get_id() { return this ? id : 0; }
        int id;
        bool is_ok() { return use <= max_slot && use >= min_slot; }
        bool is_surplus() { return use > min_slot; };

        void insert(int i, std::pair<key_type, node_type *> val)
        {
            use++;
            for (int j = use - 1; j > i; j--)
            {
                Keys[j] = Keys[j - 1];
            }
            Keys[i] = val.first;
            if (!isLeaf)
            {
                for (int j = use; j > i; j--)
                {
                    Children[j] = Children[j - 1];
                }
                Children[i] = val.second;
                // Children[i]->prev=Children[i-1];
                // Children[i-1]->next=Children[i];
            }
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
            for (int j = use - 1; j > i; j--)
            {
                Keys[j] = Keys[j - 1];
            }
            Keys[i] = k;
        }
        void remove_key(int i)
        {
            for (int j = i; j < use - 1; j++)
            {
                Keys[i] = Keys[i + 1];
            }
            use--;
        }

        void set_child(int i, node_type *n)
        {
            // if(i>0){
            //     n->prev=Children[i-1];
            // }else{
            //     n->prev=nullptr;
            // }

            // if(i<use){
            //     n->next=Children[i]->next;
            // }else{
            //     n->next=nullptr;
            // }

            // if(n->prev){
            //     n->prev->next=n;
            // }
            // if(n->next){
            //     n->next->prev=n;
            // }
            Children[i] = n;
            n->Parent = this;
        }
        node_type *get_child(int i) const { return Children[i]; }

        void remove(int i)
        {
            for (int j = i; j < use - 1; j++)
            {
                Keys[j] = Keys[j + 1];
            }

            if (!isLeaf)
            {
                for (int j = i; j < use + 1; j++)
                {
                    Children[j] = Children[j + 1];
                }
            }

            use--;
        }

        // int find_pos(const key_type &k)
        // {
        //     assert(this != nullptr);
        //     int i = 0;
        //     while (i < use && k > Keys[i])
        //         i++;
        //     return i;
        // }

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

        key_type &first_key() { return Keys[0]; }
        key_type &last_key() { return Keys[use - 1]; }
        // key_type &first_key() { return Keys[0]; }
        // key_type &last_key() { return Keys[use - 1]; }

        node_type *first_child() const { return Children[0]; }
        node_type *last_child() const { return Children[use]; }
    };
    //simple iteator
    struct loc
    {
        loc(node_type *n, int p)
        {
            node = n;
            pos = p;
        }
        key_type getKey(){
            return node->Keys[pos];
        }
        data_type getVal(){
            return node->Datas[pos];
        }
        node_type *node;
        int pos;
        loc next()
        {
            bool isLeaf = node->isLeaf;
            int use = node->use;

            int p2 = pos + 1;
            if (isLeaf)
            {
                // is the last one
                if (pos == use)
                {
                    return *this;
                }
                if (p2 == use)
                {
                    auto next = node->next;
                    if (next == nullptr)
                    {
                        return loc(node, p2);
                    }
                    else
                    {
                        return loc(next, 0);
                    }
                }
                if (p2 < use)
                {
                    return loc(node, p2);
                }
            }
            // is the last one
            if (pos == use)
            {
                return *this;
            }
            return loc(node->get_child(p2), 0);
        }
        void check() { assert(node && pos < node->use); }
        bool operator==(const loc &r)
        {
            return node == r.node && pos == r.pos;
        }
    };

    BTree()
    {
        root = create_node();
        root->isLeaf = true;
    }
    loc begin()
    {
        return left();
    }
    loc end()
    {
        loc rgt = right();
        rgt.pos++;
        return rgt;
    }
    loc left()
    {
        auto p = root;
        while (p)
        {

            p = p->Children[0];
        }
        return loc(p, 0);
    }
    loc right()
    {
        auto p = root;
        while (p)
        {
            p = p->last_child();
        }
        return loc(p, p->use - 1);
    }
    void insert(const key_type key, const data_type val)
    {
        node_type *p = root;
        while (1)
        {
            int i = find_pos(p, key);

            if (p->isLeaf)
                break;
            p = p->Children[i];
        }

        insert_aux0(p, key, val);

        if (p->use == deg + 1)
        {
            insert_fix(p);
        }
    }

    loc find(const key_type &k)
    {
        node_type *p = root;

        while (p)
        {
            int i = find_pos(p, k);

            if (p->Keys[i] == k)
                return loc(p, i);
            if (p->isLeaf)
                return loc(nullptr, 0);
            p = p->Children[i];
        }
        return loc(nullptr, 0);
    }

    //i must in btree.
    void remove(const loc &i)
    {
        if (i.node->isLeaf)
            remove_in_leaf(i);
        else
            remove_in_inner(i);
    }

    typedef union {
        void *ptr;
        char b[sizeof(void *)];
    } char_ptr;

    static int sqrt(void *n)
    {
        char_ptr p;
        p.ptr = n;
        int ret = 0;
        for (int i = 0; i < sizeof(void *); i++)
        {
            i += p.b[i];
        }
        return ret;
    }
    friend ostream &operator<<(ostream &out, const BTree &bt)
    {
        std::queue<node_type *> q;

        node_type *p = nullptr;
        if (bt.root == nullptr)
            return out;
        q.push(bt.root);
        while (!q.empty())
        {
            queue<node_type *> q2;
            while (!q.empty())
            {

                p = q.front();
                q.pop();

                if (p->isLeaf)
                    cout << "<";
                else
                    cout << "[";
                //out<<p->prev->get_id()<<"|"<<p->get_id()<<"|"<<p->next->get_id();
                for (int i = 0; i < p->use; i++)
                {
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
    inline void destroy_node(node_type *n) { delete n; }
    inline node_type *create_node()
    {
        static int i = 1;
        node_type *p = new node_type;
        i++;
        memset(p, 0, sizeof(node_type));
        p->id = i;

        return p;
    }

    //[.][q  w   e   r][.]       [.][q   c   w   e   r][.]
    //   /  /             -->       /   /   /
    // [*][abcde]                 [*][ab][de]
    //

    node_type *split_node_to_parent(node_type *node)
    {
        assert(node->use == deg + 1);
        int mid = deg / 2;
        node_type *par = node->Parent;
        if (par == nullptr)
        {
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
        for (int j = 0; j < rightNode->use; j++)
        {
            rightNode->Keys[j] = node->Keys[j + mid + 1];
        }
        if (!rightNode->isLeaf)
        {
            for (int j = 0; j < rightNode->use + 1; j++)
            {
                rightNode->Children[j] = node->Children[j + mid + 1];
                rightNode->Children[j]->Parent = rightNode;
            }
        }
        // insert to parent node
        int i = find_pos(par, node->Keys[mid]);
        par->insert(i, make_pair(node->Keys[mid], node));
        par->set_child(i + 1, rightNode);
        rightNode->prev = node;
        if (node->next)
        {
            node->next->prev = rightNode;
            rightNode->next = node->next;
        }
        else
        {
            rightNode->next = nullptr;
        }

        if (!node->isLeaf)
        {
            node->last_child()->next = nullptr;
            rightNode->first_child()->prev = nullptr;
        }

        node->next = rightNode;
        return par;
    }

    //node is full
    void insert_fix(node_type *node)
    {
        assert(node->use == deg + 1);
        node_type *n2 = split_node_to_parent(node);
        if (n2->use == deg + 1)
            insert_fix(n2);
    };
    //node is leaf and use<max_slot
    int insert_aux0(node_type *node, const key_type &k, const _Tp &v)
    {
        assert(node->isLeaf);
        int i = find_pos(node, k);
        node->insert_key(i, k);

        return i;
    }

    inline int find_pos(node_type *node, key_type k)
    {
        assert(node != nullptr);
        int i = 0;
        while (i < node->use && k > node->Keys[i])
            i++;
        return i;
    }

    //
    void remove_fix(node_type *node)
    {
        if (node->use >= min_slot)
            return;
        node_type *par = node->Parent;
        if (par == nullptr)
        { //root
            if (node->use == 0)
            {
                if (!node->isLeaf)
                {
                    root = node->Children[0];
                    root->Parent = nullptr;
                }
            }
            return;
        }
        int x = 0;
        while (x < par->use + 1 && par->Children[x] != node)
        {
            x++;
        }
        if (node->prev && node->prev->use > min_slot)
        {
            // reblance. borrow one from prev
            // index: x-1 x
            //      [p  a   ...]         [p   f   ...]
            //     / \ / \     -->       /  \ / \
            //   [.][lef][n]           [.][lef][a]
            //

            node_type *prev = node->prev;
            assert(par->Children[x] == node);
            assert(par->Children[x - 1] == prev);

            node->insert(
                0, std::make_pair(par->get_key(x - 1), prev->last_child()));

            if (!node->isLeaf && node->use > 0)
            {
                node->Children[0]->next = node->Children[1];
                node->Children[0]->prev = nullptr;
                node->Children[1]->prev = node->Children[0];
            }

            par->set_key(x - 1, prev->last_key());
            prev->use--; //simple remove last key and child
            if (!prev->isLeaf)
                prev->Children[prev->use]->next = nullptr;
            return;
        }

        // Symmetrically to prev
        // reblance. borrow one from prev
        // index: x  x+1
        //      [p  a   ...]         [p   r   ...]
        //     / \ / \     -->    /  \ / \
        //   [.][n][rig]        [.] [na][ig]
        //         /
        //       [c]
        if (node->next && node->next->use > min_slot)
        {

            node_type *next = node->next;
            assert(par->Children[x] == node);
            assert(par->Children[x + 1] == next);
            node->insert_key(node->use, par->get_key(x));
            node_type *child_r = next->first_child();

            if (!node->isLeaf)
            {
                node->Children[node->use] = child_r;
                node->Children[node->use]->Parent = node;
                node->Children[node->use - 1]->next = node->Children[node->use];
                node->Children[node->use]->prev = node->Children[node->use - 1];
                node->Children[node->use]->next = nullptr;
            }
            par->set_key(x, next->first_key());
            next->remove(0);
            if (!next->isLeaf)
                next->Children[0]->prev = nullptr;
            return;
        }
        // no brother is surplus ,so merge
        if (node->prev)
        {
            assert(node->prev->use == min_slot);

            merge_child(node->prev, node);
            // if (par == root&&par->use==) {
            //     root = node->prev;
            //     root->Parent = nullptr;
            // }
            remove_fix(par);
            return;
        }

        if (node->next)
        {
            assert(node->next->use == min_slot);
            merge_child(node, node->next);
            // if (par == root) {
            //     root = node;
            //     root->Parent = nullptr;
            // }
            remove_fix(par);
            return;
        }

        printf("next:%p,\tprev:%p\n", node->next, node->prev);
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
        while (x < par->use + 1 && par->Children[x] != next)
        {
            x++;
        }

        //(min_slot-1)+min_slot+1=2*min_slot<deg
        int old_use = prev->use; //min_slot-1
        prev->use += next->use + 1;
        prev->Keys[old_use] = par->Keys[x - 1];

        for (int j = 0; j < next->use; j++)
        {
            prev->Keys[j + min_slot] = next->Keys[j];
        }

        if (!prev->isLeaf)
        {
            for (int j = 0; j < next->use + 1; j++)
            {
                prev->Children[j + min_slot] = next->Children[j];
                prev->Children[j + min_slot]->Parent = prev;
            }

            prev->Children[min_slot - 1]->next = prev->Children[min_slot];
            prev->Children[min_slot]->prev = prev->Children[min_slot - 1];
        }

        for (int j = x - 1; j < par->use; j++)
        {
            par->Keys[j] = par->Keys[j + 1];
            par->Children[j + 1] = par->Children[j + 2];
        }
        par->use--;
        if (next->next)
        {
            next->next->prev = prev;
            prev->next = next->next;
        }
        else
        {
            prev->next = nullptr;
        }

        destroy_node(next);
    }

    // i->node is leaf
    // i->node->use is ok after remove i
    void remove_in_leaf(const loc &i)
    {

        assert(i.node->isLeaf);

        //the simplest remove
        i.node->remove(i.pos);
        if (!i.node->is_ok())
        {
            remove_fix(i.node);
        }
    }

    void remove_in_inner(const loc &i)
    {
        assert(!i.node->isLeaf);
        node_type *node = i.node;
        int p = i.pos;
        if (node_type *child = node->get_child(p))
        {
            // remove o
            //      [n  o   d]          [n  i   d]
            //      / \/ \      -->     / \/ \      --> remove i in [chi]
            //    [][chi][]           [][chi][]
            //
            node->set_key(p, child->last_key());

            remove(loc(child, child->use - 1));
        }
    }
    node_type *root;
};

} // namespace omd
