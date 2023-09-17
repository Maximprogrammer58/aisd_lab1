#include "../include/polyline.h"

int main() {
	Polyline<int> polyline(7);
	
	Point<int> point1(50, 100);
	Point<int> point2(50, 50);
	Point<int> point3(100, 50);
	Point<int> point4(100, 100);
	Point<int> point5(100, 50);
	Point<int> point6(150, 50);
	Point<int> point7(150, 100);

	polyline += point2;
	polyline += point3;
	polyline += point4;
	polyline.PushBack(point5);
	polyline.PushBack(point6);
	polyline.PushBack(point7);
	polyline.PushFront(point1);

	std::cout << "Size: " << polyline.size() << std::endl;
	std::cout << polyline << std::endl;

	return 0;
}