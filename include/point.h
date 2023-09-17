#ifndef TESTLABC_INCLUDE_POINT_H
#define TESTLABC_INCLUDE_POINT_H

#include <iostream>
#include <cmath>
#include <complex>

template<typename T>
struct Point {
	T x, y;

	Point() : x(0), y(0) {}

	Point(T x, T y) : x(x), y(y) {}

	Point(const Point<T>& point) : x(point.x), y(point.y) {}
};

template<>
struct Point<std::complex<float>> {
	float x, y;

	Point() : x(0), y(0) {}

	Point(std::complex<float> number) : x(number.real()), y(number.imag()) {}

	double Len() {
		return sqrt(pow(x, 2) + pow(y, 2));
	}
};

template<>
struct Point<std::complex<double>> {
	double x, y;

	Point() : x(0), y(0) {}

	Point(std::complex<double> number) : x(number.real()), y(number.imag()) {}

	double Len() {
		return sqrt(pow(x, 2) + pow(y, 2));
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& point) {
	stream << "(" << point.x << ", " << point.y << ")";
	return stream;
}

#endif