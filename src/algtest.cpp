#include <iostream>

template <typename T>
void swap(T *a, T *b) 
{
    T c = *a;
    *a = *b;
    *b = c;
}


template <typename T, typename cmp = std::less<T>>
void bubblesort(T*begin, T*end, cmp comp = std::less<T>{})
{
    for (size_t i = 0; i + 1 < end - begin; ++i) 
    {
        for (size_t j = 0; j + 1 < end - begin - i; ++j) 
        {
            if (begin[j + 1] < begin[j]) 
            {
                swap(begin + j, begin + j + 1);
            }
        }
    }
}



int main()
{
    int arr[] = {2, 4, 1, 7, 3, -8, 3, -4, 2, -2, 1, 4, 2, -3, -8, 6, 8, 5, 8, -3, 0};
    bubblesort<int>(arr, arr + 21);
    for (int i = 0; i < 21; i++)
    {
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}