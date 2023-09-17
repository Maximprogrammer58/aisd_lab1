#include <iostream>

#include "../include/polyline.h"

int main() {
	Polyline<double> polyline(5);
	Point<int> point(3, 5);
	std::cout << point;
	return 0;
}