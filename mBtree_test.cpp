#include"mBTree.h"

using namespace gjy;
int main(){

    BTree t;
    for(int i=0;i<30;i++)
    {
     
        t.insert(i+1,i+1);
        printf("\n***\n");
        t.print();

    }
}
