#pragma once

#include <ostream>

template <typename T>
class Array {
public:
	Array() throw();
	explicit Array(unsigned int n);
	Array(const Array& other);
	Array& operator=(Array other) throw();
	~Array();

	T& operator[](unsigned int idx);
	const T& operator[](unsigned int idx) const;

	void swap(Array<T>& other) throw();
	unsigned int size() const throw();

private:
	T* _elems;
	unsigned int _size;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& array);

#include "Array.tpp"
