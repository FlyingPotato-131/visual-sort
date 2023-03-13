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




template <typename T>
void ShakerSort(T*begin, T*end, bool(*compare)(const T, const T)) 
{
  int left = 0;
  int right = end - begin - 1;
  while (left <= right) {
    for (int i = right; i > left; --i) 
    {
      if (compare(begin[i - 1], begin[i])) 
      {
        swap(begin + i - 1, begin + i);
      }
    }
    ++left;
    for (int i = left; i < right; ++i) 
    {
      if (compare(begin[i], begin[i + 1])) 
      {
        swap(begin + i, begin + i + 1);
      }
    }
    --right;
  }
}




template <typename T>
void CombSort(T*begin, T*end, bool(*compare)(const T, const T)) 
{
    const double factor = 1.247; 
    int step = end - begin - 1;

    while (step >= 1) {
    for (int i = 0; i + step < end - begin; ++i)
    {
        if (compare(begin[i], begin[i + step])) 
        {
            swap(begin + i, begin + i + step);
        }
    }
    step /= factor;
}
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



template<typename T>
T* min_element(T* first, T* last, bool(*compare)(const T, const T))
{
    if (first == last)
        return last;

    T* smallest = first;
    ++first;

    for (; first != last; ++first)
        if (compare(*first, *smallest))
            smallest = first;

    return smallest;
}




template <typename T>
void SelectionSort(T*begin, T*end, bool(*compare)(const T, const T)) 
{
    for (auto i = begin; i != end; ++i) 
    {
        auto j = min_element(i, end, compare);
        swap(i, j);
    }
}
