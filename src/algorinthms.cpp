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


