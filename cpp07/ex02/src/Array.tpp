// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

#pragma once

#include "Array.hpp"
#include "libftpp/algorithm.hpp"
#include "libftpp/string.hpp"
#include <ostream>
#include <stdexcept>

template <typename T>
Array<T>::Array() throw()
    : _elems(),
      _size(0)
{}

template <typename T>
Array<T>::Array(unsigned int n)
    : _elems(new T[n]),
      _size(n)
{
	for (unsigned int i = 0; i < _size; ++i) {
		_elems[i] = T();
	}
}

template <typename T>
Array<T>::Array(const Array& other)
    : _elems(new T[other._size]),
      _size(other._size)
{
	for (unsigned int i = 0; i < _size; ++i) {
		_elems[i] = other._elems[i];
	}
}

template <typename T>
Array<T>& Array<T>::operator=(Array other) throw()
{
	swap(other);
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] _elems;
}

template <typename T>
T& Array<T>::operator[](unsigned int idx)
{
	if (idx >= _size) {
		throw std::out_of_range("out-of-bounds access in Array: index ("
		                        + ft::to_string(idx) + ") >= array size ("
		                        + ft::to_string(_size) + ")");
	}
	return _elems[idx];
}

template <typename T>
const T& Array<T>::operator[](unsigned int idx) const
{
	if (idx >= _size) {
		throw std::out_of_range("out-of-bounds access in Array: index ("
		                        + ft::to_string(idx) + ") >= array size ("
		                        + ft::to_string(_size) + ")");
	}
	return _elems[idx];
}

template <typename T>
void Array<T>::swap(Array<T>& other) throw()
{
	ft::swap(_elems, other._elems);
	ft::swap(_size, other._size);
}

template <typename T>
unsigned int Array<T>::size() const throw()
{
	return _size;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& array)
{
	if (array.size() == 0) {
		os << "empty array" << '\n';
		return os;
	}
	for (unsigned int i = 0; i < array.size(); ++i) {
		os << i << ": " << array[i] << '\n';
	}
	return os;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
