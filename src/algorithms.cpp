// #include "colors.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "globals.hpp"

void updatewindow(sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite){
    for (int h = 0; h < Height - 1; ++h)
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
    image->update(pixels);
    // window->clear(sf::Color::Black);
    window->draw(*sprite);
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
void bubblesort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite)
{
    for (size_t i = 0; i + 1 < end - begin; ++i) 
    {
        for (size_t j = 0; j + 1 < end - begin - i; ++j) 
        {
            if (compare(begin[j + 1], begin[j])) 
            {
                swappixels(begin + j, begin + j + 1, raw, pixels);
                // image->update(pixels);
                image->update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width, (begin + j - raw) / Width);
                image->update(pixels + 4*(begin + j + 1 - raw), 1, 1, (begin + j + 1 - raw) % Width, (begin + j + 1 - raw) / Width);
                window->clear(sf::Color::Black);
                window->draw(*sprite);
                window->display();
            }
        }
        // updatewindow(pixels, raw, image, window, sprite);
    }
}


template <typename T>
void ShakerSort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite) 
{
  int left = 0;
  int right = end - begin - 1;
  while (left <= right) {
    for (int i = right; i > left; --i) 
    {
        if (compare(begin[i], begin[i - 1])) 
        {
            swappixels(begin + i - 1, begin + i, raw, pixels);
            image->update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            image->update(pixels + 4*(begin + i - 1 - raw), 1, 1, (begin + i - 1 - raw) % Width, (begin + i - 1 - raw) / Width);
            // image->update(pixels);
            window->clear(sf::Color::Black);
            window->draw(*sprite);
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
            image->update(pixels + 4*(begin + i + 1 - raw), 1, 1, (begin + i + 1 - raw) % Width, (begin + i + 1 - raw) / Width);
            image->update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            window->clear(sf::Color::Black);
            window->draw(*sprite);
            window->display();
        }
    }
    // updatewindow(pixels, raw, image, window, sprite);
    --right;
  }
}

template <typename T>
void CombSort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite) 
{
    const double factor = 1.247; 
    int step = end - begin - 1;

    while (step >= 1) {
    for (int i = 0; i + step < end - begin; ++i)
    {
        if (compare(begin[i + step], begin[i])) 
        {
            swappixels(begin + i, begin + i + step, raw, pixels);
            image->update(pixels + 4*(begin + i - raw), 1, 1, (begin + i - raw) % Width, (begin + i - raw) / Width);
            image->update(pixels + 4*(begin + i + step - raw), 1, 1, (begin + i + step - raw) % Width, (begin + i + step - raw) / Width);
            // image->update(pixels);
            window->clear(sf::Color::Black);
            window->draw(*sprite);
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
                image->update(pixels + 4*(begin + j - raw), 1, 1, (begin + j - raw) % Width, (begin + j - raw) / Width);
                image->update(pixels + 4*(begin + j + 1 - raw), 1, 1, (begin + j + 1 - raw) % Width, (begin + j + 1 - raw) / Width);
                // image->update(pixels);
                window->clear(sf::Color::Black);
                window->draw(*sprite);
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
void SelectionSort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite) 
{
    for (auto i = begin; i != end; ++i) 
    {
        auto j = min_element(i, end, compare);
        swappixels(i, j, raw, pixels);
        // image->update(pixels);
        image->update(pixels + 4*(i - raw), 1, 1, (i - raw) % Width, (i - raw) / Width);
        image->update(pixels + 4*(j - raw), 1, 1, (j - raw) % Width, (j - raw) / Width);
        window->clear(sf::Color::Black);
        window->draw(*sprite);
        window->display();

    }
}

template<typename T, typename Pred>
T *partition(T *begin, T *end, Pred predicate, sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite){
    //int len = end - begin;
    T *left = begin + 1;
    T *right = end - 1;
    while(right - left > 0){
        if(predicate(left) == 0 && predicate(right) == 1){
            swappixels(left, right, raw, pixels);
            // image->update(pixels);
            image->update(pixels + 4*(left - raw), 1, 1, (left - raw) % Width, (left - raw) / Width);
            image->update(pixels + 4*(right - raw), 1, 1, (right - raw) % Width, (right - raw) / Width);
            window->clear(sf::Color::Black);
            window->draw(*sprite);
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
void quicksort(T *begin, T *end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite){
    // if(end - begin == 2){
    //     if(!compare(*begin, begin[1]))
    //         swap(begin, begin + 1);
    //     return;
    // }
    if(end - begin > 1){
        auto leseq = [begin, compare](T *x){return compare(*x, *begin);};
        T *pos = partition(begin, end, leseq, pixels, raw, image, window, sprite);
        // updatewindow(pixels, raw, image, window, sprite);
    
        if(compare(*pos, *begin)){
            swappixels(begin, pos, raw, pixels);
            // image->update(pixels);
            image->update(pixels + 4*(begin - raw), 1, 1, (begin - raw) % Width, (begin - raw) / Width);
            image->update(pixels + 4*(pos - raw), 1, 1, (pos - raw) % Width, (pos - raw) / Width);
            window->clear(sf::Color::Black);
            window->draw(*sprite);
            window->display();
        }
         
        quicksort(begin, pos, compare, pixels, raw, image, window, sprite);
        quicksort(pos, end, compare, pixels, raw, image, window, sprite);
    }
}