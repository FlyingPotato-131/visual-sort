// #include "colors.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "globals.hpp"

void updatewindow(sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform){
    for (int h = 0; h < Height; ++h)
    {
        for (int w = 0; w < Width; ++w)
        {
            hsv col = raw[h * Width + w];
            rgb out = hsvrgb(col);
            pixels[4 * (h * Width + w)] = out.r;
            pixels[4 * (h * Width + w) + 1] = out.g;
            pixels[4 * (h * Width + w) + 2] = out.b;
            pixels[4 * (h * Width + w) + 3] = 255;  
        }
    }
    for (int i = 0; i < Height; ++i){
        image[0].update(pixels + Width * 4 * i, 20, 1, 0, i);
        image[1].update(pixels + Width * 2 + Width * 4 * i, 20, 1, 0, i);
    }
    window->clear(sf::Color::Black);
    for(int i = 0; i < 2; i++)
        window->draw(sprite[i], transform[i]);
    window->display();
}

template <typename T>
void swap(T *a, T *b) 
{
    T c = *a;
    *a = *b;
    *b = c;
}

template<typename T>
void swappixels(T *a, T *b, T *begin, sf::Uint8 *pixels){
    int la = a - begin;
    int lb = b - begin;
    swap(a, b);
    swap(pixels + 4 * la, pixels + 4 * lb);
    swap(pixels + 4 * la + 1, pixels + 4 * lb + 1);
    swap(pixels + 4 * la + 2, pixels + 4 * lb + 2);
}

template <typename T>
void bubblesort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform)
{
    for (size_t i = 0; i + 1 < end - begin; ++i) 
    {
        for (size_t j = 0; j + 1 < end - begin - i; ++j) 
        {
            if (compare(begin[j + 1], begin[j])) 
            {
                swappixels(begin + j, begin + j + 1, raw, pixels);
                // image->update(pixels);
                // image->update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width, (begin + j - raw) / Width);
                // image->update(pixels + 4*(begin + j + 1 - raw), 1, 1, (begin + j + 1 - raw) % Width, (begin + j + 1 - raw) / Width);
                // // window->clear(sf::Color::Black);
                // window->draw(*sprite);
                if((begin + j - raw) % Width >= Width / 2)
                    image[1].update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width - Width / 2, (begin + j - raw) / Width);
                else
                    image[0].update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width, (begin + j - raw) / Width);
                if((begin + j + 1 - raw) % Width >= Width / 2)
                    image[1].update(pixels + 4*(begin + j + 1 - raw), 1, 1, (begin + j + 1 - raw) % Width - Width / 2, (begin + j + 1 - raw) / Width);
                else
                    image[0].update(pixels + 4*(begin + j + 1 - raw), 1, 1, (begin + j + 1 - raw) % Width, (begin + j + 1 - raw) / Width);
        // window->draw(*sprite, transform);
                for(int i = 0; i < 2; i++)
                    window->draw(sprite[i], transform[i]);
                window->display();
            }
        }
        // updatewindow(pixels, raw, image, window, sprite);
    }
}


template <typename T>
void ShakerSort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform) 
{
  int left = 0;
  int right = end - begin - 1;
  while (left <= right) {
    for (int i = right; i > left; --i) 
    {
        if (compare(begin[i], begin[i - 1])) 
        {
            swappixels(begin + i - 1, begin + i, raw, pixels);
            // image->update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            // image->update(pixels + 4*(begin + i - 1 - raw), 1, 1, (begin + i - 1 - raw) % Width, (begin + i - 1 - raw) / Width);
            // // image->update(pixels);
            // // window->clear(sf::Color::Black);
            // window->draw(*sprite);
            if((begin + i - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width - Width / 2, (begin + i - raw) / Width);
            else
                image[0].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            if((begin + i -1 - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin + i -1 - raw), 1, 1, (begin + i -1 - raw) % Width - Width / 2, (begin + i -1 - raw) / Width);
            else
                image[0].update(pixels + 4*(begin + i -1 - raw), 1, 1, (begin + i -1 - raw) % Width, (begin + i -1 - raw) / Width);
        // window->draw(*sprite, transform);
            for(int i = 0; i < 2; i++)
                window->draw(sprite[i], transform[i]);
            window->display();
        }
    }
    // updatewindow(pixels, raw, image, window, sprite);
    ++left;
    for (int i = left; i < right; ++i) 
    {
        if (compare(begin[i + 1], begin[i])) 
        {
            swappixels(begin + i, begin + i + 1, raw, pixels);
            // image->update(pixels);
            // image->update(pixels + 4*(begin + i + 1 - raw), 1, 1, (begin + i + 1 - raw) % Width, (begin + i + 1 - raw) / Width);
            // image->update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            // // window->clear(sf::Color::Black);
            // window->draw(*sprite);
            if((begin + i - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width - Width / 2, (begin + i - raw) / Width);
            else
                image[0].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            if((begin + i + 1 - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin + i + 1 - raw), 1, 1, (begin + i + 1 - raw) % Width - Width / 2, (begin + i + 1 - raw) / Width);
            else
                image[0].update(pixels + 4*(begin + i + 1 - raw), 1, 1, (begin + i + 1 - raw) % Width, (begin + i + 1 - raw) / Width);
        // window->draw(*sprite, transform);
            for(int i = 0; i < 2; i++)
                window->draw(sprite[i], transform[i]);
            window->display();
        }
    }
    // updatewindow(pixels, raw, image, window, sprite);
    --right;
  }
}

template <typename T>
void CombSort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform) 
{
    const double factor = 1.247; 
    int step = end - begin - 1;

    while (step >= 1) {
    for (int i = 0; i + step < end - begin; ++i)
    {
        if (compare(begin[i + step], begin[i])) 
        {
            swappixels(begin + i, begin + i + step, raw, pixels);
            // image->update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            // image->update(pixels + 4*(begin + i + step - raw), 1, 1, (begin + i + step - raw) % Width, (begin + i + step - raw) / Width);
            // // image->update(pixels);
            // // window->clear(sf::Color::Black);
            // window->draw(*sprite);
            if((begin + i - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width - Width / 2, (begin + i - raw) / Width);
            else
                image[0].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            if((begin + i + step - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin + i + step - raw), 1, 1, (begin + i + step - raw) % Width - Width / 2, (begin + i + step - raw) / Width);
            else
                image[0].update(pixels + 4*(begin + i + step - raw), 1, 1, (begin + i + step - raw) % Width, (begin + i + step - raw) / Width);
        // window->draw(*sprite, transform);
            for(int i = 0; i < 2; i++)
                window->draw(sprite[i], transform[i]);
            window->display();

        }
        // updatewindow(pixels, raw, image, window, sprite);
    }
    step /= factor;
    }
    // std::cout << "debug" << std::endl;
    for (size_t i = 0; i + 1 < end - begin; ++i) 
    {
        for (size_t j = 0; j + 1 < end - begin - i; ++j) 
        {
            if (compare(begin[j + 1], begin[j])) 
            {
                swappixels(begin + j, begin + j + 1, raw, pixels);
                // image->update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width, (begin + j - raw) / Width);
                // image->update(pixels + 4*(begin + j + 1 - raw), 1, 1, (begin + j + 1 - raw) % Width, (begin + j + 1 - raw) / Width);
                // // image->update(pixels);
                // // window->clear(sf::Color::Black);
                // window->draw(*sprite);
                if((begin + i - raw) % Width >= Width / 2)
                    image[1].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width - Width / 2, (begin + i - raw) / Width);
                else
                    image[0].update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
                if((begin + j - raw) % Width >= Width / 2)
                    image[1].update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width - Width / 2, (begin + j - raw) / Width);
                else
                    image[0].update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width, (begin + j - raw) / Width);
        // window->draw(*sprite, transform);
                for(int i = 0; i < 2; i++)
                    window->draw(sprite[i], transform[i]);
                window->display();
            }
        }
        // updatewindow(pixels, raw, image, window, sprite);
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
void SelectionSort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform) 
{
    for (auto i = begin; i != end; ++i) 
    {
        auto j = min_element(i, end, compare);
        swappixels(i, j, raw, pixels);
        // image->update(pixels);
        // image->update(pixels + 4*(i - raw), 1, 1, (i - raw) % Width, (i - raw) / Width);
        // image->update(pixels + 4*(j - raw), 1, 1, (j - raw) % Width, (j - raw) / Width);
        // window->clear(sf::Color::Black);
        if((i - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(i - raw), 1, 1, (i - raw) % Width - Width / 2, (i - raw) / Width);
            else
                image[0].update(pixels + 4*(i - raw), 1, 1, (i - raw) % Width, (i - raw) / Width);
            if((j - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(j - raw), 1, 1, (j - raw) % Width - Width / 2, (j - raw) / Width);
            else
                image[0].update(pixels + 4*(j - raw), 1, 1, (j - raw) % Width, (j - raw) / Width);
        // window->draw(*sprite, transform);
        for(int i = 0; i < 2; i++)
            window->draw(sprite[i], transform[i]);
        window->display();

    }
}

template<typename T, typename Pred>
T *partition(T *begin, T *end, Pred predicate, sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform){
    //int len = end - begin;
    T *left = begin + 1;
    T *right = end - 1;
    while(right - left > 0){
        if(predicate(left) == 0 && predicate(right) == 1){
            swappixels(left, right, raw, pixels);
            // std::cout << (left - raw) / Width << " " << (right - raw) / Width << std::endl;
            // image->update(pixels);
            if((left - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(left - raw), 1, 1, (left - raw) % Width - Width / 2, (left - raw) / Width);
            else
                image[0].update(pixels + 4*(left - raw), 1, 1, (left - raw) % Width, (left - raw) / Width);
            if((right - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(right - raw), 1, 1, (right - raw) % Width - Width / 2, (right - raw) / Width);
            else
                image[0].update(pixels + 4*(right - raw), 1, 1, (right - raw) % Width, (right - raw) / Width);
            // window->clear(sf::Color::Black);
            for(int i = 0; i < 2; i++)
                window->draw(sprite[i], transform[i]);
            window->display();
            // left ++;
            // right --;
        }else if(predicate(right) == 0){
            right --;
        }else if(predicate(left) == 1){
            left ++;
        }
    }
    return left;
}

template<typename T>
void quicksort(T *begin, T *end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform){
    // if(end - begin == 2){
    //     if(!compare(*begin, begin[1]))
    //         swap(begin, begin + 1);
    //     return;
    // }
    if(end - begin > 1){
        auto leseq = [begin, compare](T *x){return compare(*x, *begin);};
        T *pos = partition(begin, end, leseq, pixels, raw, image, window, sprite, transform);
        // updatewindow(pixels, raw, image, window, sprite);
        // std::cout << (begin - raw) / Width << " " << (pos - raw) / Width << "; ";
        // std::cout << (begin - raw) / Width << " " << compare(*pos, *begin) << " ";
    
        if(compare(*pos, *begin)){
            swappixels(begin, pos, raw, pixels);
            // image->update(pixels);
            if((begin - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(begin - raw), 1, 1, (begin - raw) % Width - Width / 2, (begin - raw) / Width);
            else
                image[0].update(pixels + 4*(begin - raw), 1, 1, (begin - raw) % Width, (begin - raw) / Width);
            if((pos - raw) % Width >= Width / 2)
                image[1].update(pixels + 4*(pos - raw), 1, 1, (pos - raw) % Width - Width / 2, (pos - raw) / Width);
            else
                image[0].update(pixels + 4*(pos - raw), 1, 1, (pos - raw) % Width, (pos - raw) / Width);
            // window->clear(sf::Color::Black);
            for (int i = 0; i < 2; ++i)
                window->draw(sprite[i], transform[i]);
            window->display();
        }
         
        quicksort(begin, pos, compare, pixels, raw, image, window, sprite, transform);
        quicksort(pos, end, compare, pixels, raw, image, window, sprite, transform);
    }
}

template <typename T>
void merge(T *first, T *middle, T *last, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform)
{
    // std::vector<T> tmp(abs(first - last));
    T *tmp = new T[abs(first - last)];
    // T *end = tmp + abs(first - last); 
    T *i = first;
    T *j = middle;
    auto k = tmp;

    while (i != middle && j != last) {
        if (compare(*i, *j)) {
            *k++ = *i++;
        } else {
            *k++ = *j++;
        }
    }

    k = std::copy(i, middle, k);
    k = std::copy(j, last, k);

    std::copy(tmp, tmp + abs(first - last), first);
    updatewindow(pixels, raw, image, window, sprite, transform);
}

template <typename T>
void merge_sort(T *first, T *last, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform)
{
    if (abs(first - last) <= 1) {
        return;
    }

    T *middle = std::next(first, abs(first - last) / 2);
    merge_sort(first, middle, compare, pixels, raw, image, window, sprite, transform);
    merge_sort(middle, last, compare, pixels, raw, image, window, sprite, transform);
    // std::inplace_merge(first, middle, last, compare);
    merge(first, middle, last, compare, pixels, raw, image, window, sprite, transform);
}

const int RUN = 32;

template <typename T>
void insertionSort(T*first, int left, int right, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform)
{
    for (int i = left + 1; i <= right; i++)
    {
        T temp = first[i];
        int j = i - 1;
        while (j >= left && !compare(first[j], temp))
        {
            first[j+1] = first[j];
            // pixels[4 * (j + 1)] = pixels[4 * j];
            // pixels[4 * (j + 1) + 1] = pixels[4 * j] + 1;
            // pixels[4 * (j + 1) + 2] = pixels[4 * j] + 2;
            // image->update(pixels + 4*(j + 1), 1, 1, (j + 1) % Width, (j + 1) / Width);
            j--;
            // window->clear(sf::Color::Black);
            // window->draw(*sprite);
            // window->display();
        }
        first[j+1] = temp;
        updatewindow(pixels, raw, image, window, sprite, transform);
    }
}

template <typename T>
void timmerge(T*first, int l, int m, int r, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform)
{
    
    int len1 = m - l + 1, len2 = r - m;
    T left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = first[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = first[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2)
    {
        if (compare(left[i], right[j]))
        {
            first[k] = left[i];
            i++;
        }
        else
        {
            first[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1)
    {
        first[k] = left[i];
        k++;
        i++;
    }

    while (j < len2)
    {
        first[k] = right[j];
        k++;
        j++;
    }
    updatewindow(pixels, raw, image, window, sprite, transform);
}

template <typename T>
void timSort(T*first, T*last, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite, sf::RenderStates *transform)
{
    
    for (int i = 0; i < last - first; i+=RUN)
        insertionSort(first, i, std::min((i + RUN - 1), int(last - first - 1)), compare, pixels, raw, image, window, sprite, transform);

    for (int size = RUN; size < last - first; size = 2 * size)
    {
        for (int left = 0; left < last - first; left += 2 * size)
        {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (int(last - first) - 1));
            if(mid < right)
                timmerge(first, left, mid, right, compare, pixels, raw, image, window, sprite, transform);
        }
    }
}
