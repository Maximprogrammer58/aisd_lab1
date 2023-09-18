#ifndef TESTLABC_INCLUDE_POLYLINE_H
#define TESTLABC_INCLUDE_POLYLINE_H

#include <utility>
#include <stdexcept>

#include "point.h"
#include "random.h"

const int kGrowth = 5;

template<typename T>
class Polyline
{
	Point<T>** data_;
	int size_, capacity_;

public:

	Polyline(int capacity) : capacity_(capacity), size_(0) {
		data_ = new Point<T>*[capacity_];
	}

	Polyline(T x, T y) : size_(0) {
		capacity_ = kGrowth;
		data_ = new Point<T>*[capacity_]();
		data_[0] = new Point<T>(x, y);
		size_++;
	}

	Polyline(int size, T x1, T x2, T y1, T y2) : size_(size) {
		capacity_ = size_ + kGrowth;
		data_ = new Point<T>*[capacity_]();
		for (int i = 0; i < size_; ++i) {
			data_[i] = new Point<T>(Random(x1, x2), Random(y1, y2));
		}
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

	Polyline<T>& operator+=(const Point<T>& point) {
		if (size_ >= capacity_) {
			capacity_ += kGrowth;
			Point<T>** temp = new Point<T>*[capacity_]();

			for (int i = 0; i < size_; ++i) {
				temp[i] = data_[i];
			}

			delete[] data_;
			data_ = temp;
		}

		data_[size_] = new Point<T>(point);
		size_++;

		return *this;
	}

	Polyline<T> operator+(const Point<T>& point) {
		Polyline<T> add_res(*this);
		add_res += point;
		return add_res;
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

	Polyline<T>& operator+=(const Polyline<T>& other) {
		if (size_ + other.size_ > capacity_) {
			capacity_ = size_ + other.size_ + kGrowth;
			Point<T>** temp = new Point<T>*[capacity_]();

			for (int i = 0; i < size_; ++i) {
				temp[i] = data_[i];
			}

			delete[] data_;
			data_ = temp;
		}

		for (int i = 0; i < other.size_; ++i) {
			*this += *other.data_[i];
		}

		return *this;
	}

	Polyline<T> operator+(const Polyline<T>& other) {
		Polyline<T> add_res(*this);
		add_res += other;
		return add_res;
	}

	double Length() {
		double length = 0;
		for (int i = 0; i < size_ - 1; ++i) {
			length += (*data_[i]).Distance(*data_[i + 1]);
		}
		return length;
	}

	void PushBack(const Point<T>& point) {
		if (size_ >= capacity_) {
			capacity_ += kGrowth;
			Point<T>** temp = new Point<T>*[capacity_]();

			for (int i = 0; i < size_; ++i) {
				temp[i] = data_[i];
			}

			delete[] data_;
			data_ = temp;
		}

		data_[size_] = new Point<T>(point);
		size_++;
	}

	void PushFront(const Point<T>& point) {
		if (size_ >= capacity_) {
			capacity_ += kGrowth;
			Point<T>** temp = new Point<T>*[capacity_]();

			for (int i = 0; i < size_; ++i) {
				temp[i] = data_[i];
			}

			delete[] data_;
			data_ = temp;
		}

		Point<T>** temp = new Point<T>*[capacity_]();

		for (int i = 0; i < size_; ++i) {
			temp[i + 1] = data_[i];
		}

		temp[0] = new Point<T>(point);
		delete[] data_;
		data_ = temp;
		++size_;
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

template<typename T>
bool operator==(const Polyline<T>& line1, const Polyline<T>& line2) {
	if (line1.size() != line2.size()) {
		throw std::runtime_error("Different number of vertices");
	}

	bool be_equal = true;
	for (int i = 0; i < line1.size(); ++i) {
		if (line1[i] != line2[i]) {
			be_equal = false;
		}
	}

	bool be_equal_reverse = true;
	for (int i = 0; i < line1.size(); ++i) {
		if (line1[i] != line2[line1.size() - i - 1]) {
			be_equal_reverse = false;
		}
	}

	return (be_equal || be_equal_reverse);
}

template<typename T>
bool operator!=(const Polyline<T>& line1, const Polyline<T>& line2) {
	return (!(line1 == line2));
}

#endif