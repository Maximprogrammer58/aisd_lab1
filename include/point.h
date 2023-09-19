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

	Point<T>& operator=(const Point<T> other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	double Distance(const Point<T>& next_point) {
		return sqrt(pow(next_point.x - x, 2) + pow(next_point.y - y, 2));
	}
};

template<typename U>
struct Point<std::complex<U>> {
	float x, y;

	Point() : x(0), y(0) {}

	Point(std::complex<U> number) : x(number.real()), y(number.imag()) {}

	Point<std::complex<U>>& operator=(const Point<std::complex<U>> other) {
		x = other.x;
		y = other.y;
		return *this;
	}

	double Distance(const Point<std::complex<U>>& next_point) {
		return sqrt(pow(next_point.x - x, 2) + pow(next_point.y - y, 2));
	}

	double Len() {
		return sqrt(pow(x, 2) + pow(y, 2));
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Point<T>& point) {
	stream << "(" << point.x << ", " << point.y << ")";
	return stream;
}

template<typename T>
bool operator==(const Point<T>& point1, const Point<T>& point2) {
	const double kEpsilon  = 1.0E-5;
	if ((std::abs(point1.x - point2.x) <= kEpsilon) && (std::abs(point1.y - point2.y) <= kEpsilon)) {
		return true;
	}
	return false;
}

template<>
bool operator==(const Point<int>& point1, const Point<int>& point2) {
		if ((point1.x == point2.x) && (point1.y == point2.y)) {
			return true;
		}
	return false;
}

template<typename T>
bool operator!=(const Point<T>& point1, const Point<T>& point2) {
	return (!(point1 == point2));
}

#endif