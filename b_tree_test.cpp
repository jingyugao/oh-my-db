#include "b_tree.h"
#include <random>
#include <set>
using namespace omd;
const int N = 30;
int main()
{

    b_tree<int, int, 5> bt;
    set<int> a;

    for (int i = 0; i < N; i++) {
        int k = 0;
        do {
            k = rand() % 100;
        } while (a.find(k) != a.end());
        a.insert(k);
        printf("\n***insert %d ***\n", k);
        bt.insert(k, i + 1);

        cerr << bt;
    }

    for (auto i = a.begin(); i != a.end(); i++) {
        printf("\n***remove %d ***\n", *i);

        auto l = bt.find(*i);
        bt.remove(l);
        cerr<<bt;
    }
}
