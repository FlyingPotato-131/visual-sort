template <typename T>
void swap(T *a, T *b) 
{
    T c = *a;
    *a = *b;
    *b = c;
}


template <typename T>
void bubblesort(T*begin, T*end, bool(*compare)(const T, const T))
{
    for (size_t i = 0; i + 1 < end - begin; ++i) 
    {
        for (size_t j = 0; j + 1 < end - begin - i; ++j) 
        {
            if (compare(begin[j + 1], begin[j])) 
            {
                swap(begin + j, begin + j + 1);
            }
        }
    }
}


