#pragma once

#include "Optional.hpp"
#include "common.hpp"

namespace utils {

template <typename T>
Optional<T>::Optional()
    : _has_value()
{}

template <typename T>
Optional<T>::Optional(const T& value)
    : _value(value),
      _has_value(true)
{}

template <typename T>
Optional<T>::Optional(const Optional<T>& other)
    : _value(other.value_or(T())),
      _has_value(other._has_value)
{}

template <typename T>
Optional<T>::~Optional()
{}

template <typename T>
Optional<T>& Optional<T>::operator=(T value)
{
	swap(value);
	_has_value = true;
	return *this;
}

template <typename T>
Optional<T>& Optional<T>::operator=(Optional<T> other)
{}

template <typename T>
void Optional<T>::swap(Optional<T>& other)
{
	if (_has_value && other._has_value) {
		utils::swap(_value, other._value);
		utils::swap(_has_value, other._has_value);
	}
	else if (_has_value) {
		other(*this);
		_has_value = false;
	}
	else if (other._has_value) {
		*this(other);
		other._has_value = false;
	}
}

template <typename T>
void Optional<T>::reset() throw()
{}

template <typename T>
template <typename F>
Optional<T> Optional<T>::and_then(F f)
{}

template <typename T>
template <typename F>
Optional<T> Optional<T>::and_then(F f) const
{}

template <typename T>
template <typename F>
Optional<T> Optional<T>::or_else(F f)
{}

template <typename T>
template <typename F>
Optional<T> Optional<T>::or_else(F f) const
{}

template <typename T>
Optional<T>::operator bool() const throw()
{}

template <typename T>
bool Optional<T>::has_value() const throw()
{}

template <typename T>
T& Optional<T>::value()
{}

template <typename T>
const T& Optional<T>::value() const
{}

template <typename T>
T& Optional<T>::value_or(T& default_value)
{}

template <typename T>
const T& Optional<T>::value_or(const T& default_value) const
{}

} // namespace utils
