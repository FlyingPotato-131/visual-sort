#include <iostream>
#include "colors.hpp"

int main(){
	rgb c = hsvrgb({0, 1, 1});
	std::cout << c.r << " " << c.g << " " << c.b << std::endl;
}