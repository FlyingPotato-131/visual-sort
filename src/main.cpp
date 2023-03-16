#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
// #include <SFML/Transform.hpp>
#include "colors.hpp"
#include <string>
#include <random>
#include "algorithms.cpp"
// #include <thread>
// #include <mutex>
#include <condition_variable>
// #include <queue>
#include <unistd.h>

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
		if(alg != "bubblesort" && alg != "shakersort" && alg != "combsort" && alg != "selectionsort" && alg != "quicksort" && alg != "mergesort" && alg != "timsort"){
			std::cout << "Not a valid sorting algorithm" << std::endl;
			return 0;
		}
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<> dis(0, 359);	
		std::uniform_real_distribution<> fdis(0, 1);
		sf::RenderWindow window(sf::VideoMode(resWidth, resHeight), "Sort Render");
		sf::Uint8 *pixels = new sf::Uint8[Width * Height * 4];
		hsv *raw = new hsv[Width * Height];
		sf::Texture *image = new sf::Texture[3];
		image[0].create(Width / 2, Height);
		image[1].create(Width / 2, Height);
		// sf::Sprite sprite(image[0]);	
		sf::Sprite *sprite = new sf::Sprite[3];
		// sprite.setScale(48, 48);
		sf::Transform *shear = new sf::Transform[3];
		 
		shear[0] = sf::Transform(15, 0, 960 - 7.5 * Width,
	 			  				 10, 20, 1050 - 35 * Height,
	 							   0, 0, 0);

		shear[1] = sf::Transform(15, 0, 960,
	 			  				 -10, 20, 1050 - 25 * Height,
	 							   0, 0, 0);

		sf::RenderStates *rendershear = new sf::RenderStates[3];
		for (int i = 0; i < 3; ++i)
			{
				rendershear[i] = sf::RenderStates(shear[i]);
				sprite[i] = sf::Sprite(image[i]);
			}	
		// sf::Shader shader = sf::Shader();
		// shader.loadFromFile("shader.glsl", sf::Shader::Fragment);
		// shader.setUniform("u_resolution", sf::Glsl::Vec2(Width, Height));
		// shader.setParameter("texture", sf::Shader::CurrentTexture);
		for (int h = 0; h < Height; ++h)
		{
			for (int w = 0; w < Width; ++w)
			{
				int hue = dis(rng);
				float sat = fdis(rng);
				hsv col = {hue, sat, 1};
				raw[h * Width + w] = col;
			}
		}
		
		updatewindow(pixels, raw, image, &window, sprite, rendershear);

		sleep(2);

		if(alg == "bubblesort"){
			bubblesort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
		   	for (int h = 0; h < Height; ++h)
	     	{
       			bubblesort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "shakersort"){
        	ShakerSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			ShakerSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "combsort"){
        	CombSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			CombSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "selectionsort"){
        	SelectionSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			SelectionSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "quicksort"){
        	quicksort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
	     		// std::cout << h << std::endl;
       			quicksort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "mergesort"){
        	merge_sort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			merge_sort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
       		}
       		std::cout << "sorted hue" << std::endl;
        }else if(alg == "timsort"){
			timSort<hsv>(raw, raw + Width * Height, lesssat, pixels, raw, image, &window, sprite, rendershear);
        	std::cout << "sorted saturation" << std::endl;
        	for (int h = 0; h < Height; ++h)
	     	{
       			timSort<hsv>(raw + h * Width, raw + h * Width + Width, lesshue, pixels, raw, image, &window, sprite, rendershear);	
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
	       	updatewindow(pixels, raw, image, &window, sprite, rendershear);
		}
	}else{
		std::cout << "please specify a sorting algorithm" << std::endl;
		return 0;
	}
}