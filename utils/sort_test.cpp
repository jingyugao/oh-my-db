#include<iostream>
#include<random>

#include"sort.h"

void check(int *A,int size){


    
    for(size_t i = 0; i < size-1; i++)
    {
        assert(A[i]<=A[i+1]);
    }

}


int main()
{

    std::srand(time(0));
    
    int size=10240;
    int *A=new int[size];
    for(int i=0;i<size;i++){
        A[i]=rand();
    }
	Inplace_MergeSort(A, 0, size-1);
 
	// Printing the sorted data.
	cout<<"\nSorted Data ";
	for (int i = 0; i < size; i++)
        cout<<"->"<<A[i];
 
	return 0;
}