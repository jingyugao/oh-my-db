#define BTREE_DEBUG
#include "b_plus_tree.h"
#include <random>

using namespace omd;

template <int Slots, typename Type>
struct btree_traits_nodebug : stx::btree_default_map_traits<Type, Type> {
    static const bool selfverify = true;
    static const bool debug = false;

    static const int leafslots = Slots;
    static const int innerslots = Slots;
};

int main()
{
    srand(time(nullptr));

    bplustree<int, int, btree_traits_nodebug<5,int> > bpt1;
    for (int i = 0; i < 100; i++) {

        bpt1.insert(rand(), bpt1.size());
    }

    bpt1.print(std::cout);
}