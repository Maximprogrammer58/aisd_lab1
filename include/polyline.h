#ifndef TESTLABC_INCLUDE_POLYLINE_H
#define TESTLABC_INCLUDE_POLYLINE_H

#include <utility>

#include "point.h"

const int kGrowth = 5;

template<typename T>
class Polyline
{
	Point<T>** data_;
	int size_, capacity_;

	double Distance(const Point<T>& pt1, const Point<T>& pt2) {
		return sqrt(pow(pt2.x - pt1.x, 2) + pow(pt2.y - pt1.y, 2));
	}

public:

	Polyline(int capacity) : capacity_(capacity), size_(0) {
		data_ = new Point<T>*[capacity_];
	}

	Polyline(int start, int end) {
		size_ = end - start + 1;
		capacity_ = size_ + kGrowth;
		data_ = new Point<T>*[capacity_];
	}

	Polyline(const Polyline<T>& other) : Polyline(other.capacity_) {
		size_ = other.size_;
		for (int i = 0; i < size_; ++i) {
			data_[i] = new Point<T>(*other.data_[i]);
		}
	}

	void swap(Polyline<T>& other) noexcept {
		std::swap(data_, other.data_);
		std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}

	Polyline<T>& operator=(Polyline<T> other) {
		swap(other);
		return *this;
	}

	int size() const {
		return size_;
	}

	int capacity() const {
		return capacity_;
	}

	const Point<T>& operator[](int index) const {
		if ((index < 0) && (index >= size_)) {
			throw std::out_of_range("Index out of range");
		}
		return *data_[index];
	}

	Point<T>& operator[](int index) {
		if ((index < 0) && (index >= size_)) {
			throw std::out_of_range("Index out of range");
		}
		return *data_[index];
	}

	double Length() {
		double length = 0;
		for (int i = 0; i < size_ - 1; ++i) {
			length += Distance(*data_[i], *data_[i + 1]);
		}
		return length;
	}

	~Polyline() {
		if (data_ != nullptr) {
			for (int i = 0; i < size_; ++i) {
				delete data_[i];
			}
			size_ = 0;
			capacity_ = 0;
			delete[] data_;
			data_ = nullptr;
		}
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Polyline<T>& line) {
	stream << "[ ";
	for (int i = 0; i < line.size(); ++i) {
		if (i == (line.size() - 1)) {
			stream << line[i];
		}
		else {
			stream << line[i] << ", ";
		}
	}
	stream << " ]";
	return stream;
}

#endif