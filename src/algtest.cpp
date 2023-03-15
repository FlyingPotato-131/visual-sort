#include <iostream>
#include "algorithms-basic.cpp"


bool compare(int a, int b)
{
    return a > b;
}

int main()
{
    int arr[] = {2, 4, 1, 7, 3, -8, 3, -4, 2, -2, 1, 4, 2, -3, -8, 6, 8, 5, 8, -3, 0};
    merge_sort<int>(arr, arr + 21, compare);
    for (int i = 0; i < 21; i++)
    {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}



