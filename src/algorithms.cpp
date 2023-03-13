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
    window->clear(sf::Color::Black);
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


template <typename T>
void bubblesort(T*begin, T*end, bool(*compare)(const T, const T), sf::Uint8 *pixels, hsv *raw, sf::Texture *image, sf::RenderWindow *window, sf::Sprite *sprite)
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
        updatewindow(pixels, raw, image, window, sprite);
    }
}


