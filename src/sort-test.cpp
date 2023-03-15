#include <iostream>
#include "algorithms-basic.cpp"

bool cmp(int a, int b){return a < b;}

int main(){
	int a[] = {0, -2, 5, -3, 9, 0, 9, -1, -1, 8, -9, 9, -8, -6, -6, -5, -1, 6, 7, 4, 6, 3, -2, 6, -8};
	qsort<int>(a, a + 25, cmp);
	for (int i = 0; i < 25; ++i)
	{
		std::cout << a[i] << " ";	
	}
	std::cout << std::endl;
}