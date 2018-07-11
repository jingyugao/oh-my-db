#include"mBTree.h"
#include<random>
#include<set>
using namespace gjy;
const int N=30;
int main(){

    BTree t;
    set<int> a;
   
    for(int i=0;i<N;i++)
    {
        int k=0;
        do{
            k=rand()%100;
        }while(a.find(k)!=a.end());
        a.insert(k);
        printf("\n***insert %d ***\n",k);
        t.insert(k,i+1);
        t.print();

    }
}
