#include <array>
#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include<map>
#if 0
#define logLine(d) printf("%d %d\n", d, __LINE__)
#else
#define logLine(x) void(0);
#endif
using namespace std;
namespace gjy {

    
	template <class _Key, class _Tp, size_t deg = 4, class _Compare = std::less<_Key>>
	//class _Alloc = std::allocator<std::pair<const _Key, _Tp>>>
	class b_tree {

		//  struct inner_node;
		//   typedef inner_node node_type;

		//   struct node_base {
		//       bool isLeaf;
		//      unsigned short use;
		//      inner_node *parent;
		//  };

		//  struct inner_node : public node_base {
		//      //typedef typename _Alloc::template rebind<inner_node>::other alloc_type;
		//      _Key Keys[deg + 1]; //last is sentiel
		//      inner_node * Children[deg + 2];
		//  };
		//struct leaf_node:public leaf_node{
		//    value_type Keys[deg+1];//last is sentiel
		//}
		struct node_type{
			bool isLeaf;
			unsigned short use;
			inner_node *parent;
			_Key Keys[deg + 1]; //last is sentiel
			node_type * Children[deg + 2];
		};

		

	public:
		typedef _Key key_type;
		typedef _Tp data_type;
		typedef std::pair<key_type, data_type> value_type;
		typedef _Compare 	 key_compare;

		b_tree(){
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
				fix_aux(p);
			}
		}

		friend ostream& operator<<(ostream& out, const b_tree&bt){
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
						out << "<";
					else
						out << "[";

					for (int i = 0; i < p->use; i++) {
						out << p->Keys[i] << " ";
						if (!p->isLeaf)
							q2.push(p->Children[i]);
					}
					if (p->isLeaf)
						out << ">\t";
					else
						out << "]\t";
					if (p->use != 0 && !p->isLeaf)
						q2.push(p->Children[p->use]);
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
			node_type *par = node->parent;
			if (par == nullptr) {
				par = create_node();
				par->isLeaf = false;
				par->use = 0;
				root = par;
			}

			node->use = deg / 2;
			node_type *rightNode = create_node();
			rightNode->isLeaf = node->isLeaf;
			rightNode->parent = par;
			node->parent = par;
			rightNode->use = deg - deg / 2;
			//std::copy
			for (int j = 0; j < rightNode->use; j++) {
				rightNode->Keys[j] = node->Keys[j + mid + 1];
				if (!rightNode->isLeaf) {
					rightNode->Children[j] = node->Children[j + mid + 1];
					rightNode->Children[j]->parent = rightNode;
				}
			}
			if (!rightNode->isLeaf) {
				rightNode->Children[rightNode->use] = node->Children[deg + 1];
				node->Children[deg + 1]->parent = rightNode;
			}
			// insert to parent node
			size_t i = find_pos(par, node->Keys[mid]);
			for (int j = par->use; j > i; j--) {

				par->Children[j + 1] = par->Children[j];
				par->Keys[j] = par->Keys[j - 1];
			}

			par->Children[i + 1] = rightNode;
			par->Children[i] = node; //left node
			par->Keys[i] = node->Keys[mid];
			par->use++;
			return par;
		}

		//node is full
		void fix_aux(node_type *node)
		{
			assert(node->use == deg + 1);
			node_type *n2 = split_node_to_parent(node);
			if (n2->use == deg + 1)
				fix_aux(n2);
		};

		size_t insert_aux0(node_type *node, const _Key &k, const _Tp &v)
		{
			size_t i = find_pos(node, k);
			for (int j = node->use; j > i; j--) {
				node->Keys[j] = node->Keys[j - 1];
			}
			node->Keys[i] = k;
			(void)v;
			node->use++;
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
		struct loc{
			node_type *node;
			size_t pos;
		};
		loc find(const key_type&k){
			node_type*p = root;
			while (p){
				size_t i = find_pos(p, k);
				if (p->Keys[i] == k)
					return loc{ p, i };
				if (p->isLeaf)
					return loc{ nullptr, 0 };
				p = p->Children[i];
			}
		}
		//i must in btree.
		void remove(const loc &i){



		}
		node_type *root;
	};



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
	//             fix_aux(p);
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
	//         // insert to parent node
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
	//     void fix_aux(BTreeNode *node)
	//     {
	//         assert(node->use == deg + 1);
	//         BTreeNode *n2 = split_node_to_parent(node);
	//         if (n2->use == deg + 1)
	//             fix_aux(n2);
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
} // namespace gjy
