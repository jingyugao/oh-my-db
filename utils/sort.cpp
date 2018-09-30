#include"sort.h"


/* 原地归并
*  可二路归并亦可与插入排序相结合，如代码
*/
//reverse array
void reverse(int arr[], int size)
{
    int left = 0;
    int right = size -1;
    while(left < right)
    {
        int temp = arr[left];
        arr[left++] = arr[right];
        arr[right--] = temp;
    }
}
 
// swap [arr,arr+headSize) and [arr+headSize,arr+headSize+endSize)
void SwapMemory(int arr[], int headSize, int endSize)
{
    reverse(arr, headSize);
    reverse(arr + headSize, endSize);
    reverse(arr, headSize + endSize);
}
 
void Inplace_Merge(int arr[], int beg, int mid, int end)
{
    int i = beg;     // 指示有序串1
    int j = mid + 1; // 指示有序串2
    while(i < j && j <= end) //原地归并结束的条件。
    {
        while(i < j && arr[i] <= arr[j])
        {
            ++i;
        }
        int index = j;
        while(j <= end && arr[j] <= arr[i])
        {
            ++j;
        }
        SwapMemory(&arr[i], index-i, j-index);//swap [i,index) and [index,j)
        i += (j-index);
    }
}

void Inplace_MergeSort(int arr[], int beg, int end)
{
    if(beg < end)
    {
        int mid = (beg + end) / 2;
        Inplace_MergeSort(arr, beg, mid);
        Inplace_MergeSort(arr, mid+1, end);
        Inplace_Merge(arr, beg, mid, end);
    }
}