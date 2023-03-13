#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "colors.hpp"

int const Width = 1920;
int const Height = 1080;

int main(){
	rgb c = hsvrgb({100, 0.6, 0.4});
	std::cout << c.r << " " << c.g << " " << c.b << std::endl;
	sf::RenderWindow window(sf::VideoMode(Width, Height), "Sort Render");
	sf::Uint8 *pixels = new sf::Uint8[Width * Height * 4];
	sf::Texture image;
	image.create(Width, Height);
	sf::Sprite sprite(image);	
	while (window.isOpen()){
	    sf::Event event;
        while (window.pollEvent(event))
       	{
           	if (event.type == sf::Event::Closed){
               	window.close();
               	//deletetree(object);
           	}
       	}
		for (int h = 0; h < Height; ++h)
		{
			for (int w = 0; w < Width; ++w)
			{
				hsv col = {w % 360, 1, 1};
				rgb out = hsvrgb(col);
				pixels[w * h] = out.r;
				pixels[w * h + 1] = out.g;
				pixels[w * h + 2] = out.b;
				pixels[w * h + 3] = 255;	
			}
		}
		image.update(pixels);
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}
}