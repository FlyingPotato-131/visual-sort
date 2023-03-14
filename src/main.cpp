#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "colors.hpp"
#include <string>
#include <random>
#include "algorithms.cpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

int main(int argc, char *argv[]){
	if(argc < 2){
		std::cout << "Usage: rendersort [-h] [-l] [-a ALGORITHM]" << std::endl;
		return 0;
	}
	std::string tmp(argv[1]);
	if(tmp == "-h"){
		std::cout << "Usage: rendersort [-h] [-l] [-a ALGORITHM]" << std::endl;
		return 0;
	}
	if(tmp == "-l"){
		std::cout << alglist << std::endl;
		std::cout << std::endl;
		return 0;
	}
	if(tmp != "-a"){
		std::cout << "Unknown option: " << tmp << std::endl;
	}
	if(argc > 2){
		std::string alg(argv[2]);
		if(alg != "bubblesort" && alg != "shakersort" && alg != "combsort" && alg != "selectionsort" && alg != "quicksort"){
			std::cout << "Not a valid sorting algorithm" << std::endl;
			return 0;
		}
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<> dis(0, 359);	
		std::uniform_real_distribution<> fdis(0, 1);
		sf::RenderWindow window(sf::VideoMode(Width, Height), "Sort Render");
		sf::Uint8 *pixels = new sf::Uint8[Width * Height * 4];
		hsv *raw = new hsv[Width * Height];
		sf::Texture image;
		image.create(Width, Height);
		sf::Sprite sprite(image);	
		sprite.setScale(48, 48);
		for (int h = 0; h < Height - 1; ++h)
		{
			for (int w = 0; w < Width; ++w)
			{
				int hue = dis(rng);
				float sat = fdis(rng);
				hsv col = {hue, sat, 1};
				raw[h * Width + w] = col;
			}
		}
		
		updatewindow(pixels, raw, &image, &window, &sprite);

		if(alg == "bubblesort"){
			bubblesort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, &image, &window, &sprite);
        	std::cout << "sorted saturation" << std::endl;
		   	for (int h = 0; h < Height; ++h)
	     	{
       			bubblesort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, &image, &window, &sprite);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "shakersort"){
        	ShakerSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, &image, &window, &sprite);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			ShakerSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, &image, &window, &sprite);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "combsort"){
        	CombSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, &image, &window, &sprite);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			CombSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, &image, &window, &sprite);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "selectionsort"){
        	SelectionSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, &image, &window, &sprite);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			SelectionSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, &image, &window, &sprite);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "quicksort"){
        	quicksort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, &image, &window, &sprite);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			quicksort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, &image, &window, &sprite);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }

		while (window.isOpen()){
		    sf::Event event;
	        while (window.pollEvent(event))
	       	{
	           	if (event.type == sf::Event::Closed){
	               	window.close();
	               	return 0;
	           	}
	       	}
	       	updatewindow(pixels, raw, &image, &window, &sprite);
		}
	}else{
		std::cout << "please specify a sorting algorithm" << std::endl;
		return 0;
	}
}