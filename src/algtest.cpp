#include <iostream>
#include "timsort.cpp"


bool compare(int a, int b)
{
    return a > b;
}

int main()
{
    int arr[] = {3, 6, 2, 6, 2, 7, 4, 6, 7, 1};
    timSort<int>(arr, arr + 10, compare);
    for (int i = 0; i < 10; i++)
    {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}

