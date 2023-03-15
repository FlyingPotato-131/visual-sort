#include <bits/stdc++.h>

struct rgb{
	int r, g, b; //from 0 to 255
};

struct hsv{
	int h; // from 0 to 360
	float s, v; // from 0 to 1
};

rgb hsvrgb(hsv col){
	float c = col.s * col.v;
	float x = c * (1 - fabs(fmod(col.h/60.f, 2) - 1));
	float m = col.v - c;
	int C = (c + m) * 255;
	int X = (x + m) * 255;
	int O = m * 255;
	if(col.h >= 0 && col.h < 60)
		return {C, X, O};
	if(col.h >= 60 && col.h < 120)
		return {X, C, O};
	if(col.h >= 120 && col.h < 180)
		return {O, C, X};
	if(col.h >= 180 && col.h < 240)
		return {O, X, C};
	if(col.h >= 240 && col.h < 300)
		return {X, O, C};
	else
		return {C, O, X};
}


bool lesssat(hsv c1, hsv c2) {return c1.s > c2.s;}
bool lesshue(hsv c1, hsv c2) {return c1.h < c2.h;}


std::ostream &operator<<(std::ostream &out, hsv c){
	std::cout << c.h << " " << c.s << " " << c.v;
	return out;
}