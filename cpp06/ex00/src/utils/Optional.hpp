#pragma once

namespace utils {

template <typename T>
class Optional {
public:
	Optional();
	explicit Optional(const T& value);
	Optional(const Optional<T>& other);
	~Optional();

	Optional& operator=(T value);
	Optional& operator=(Optional<T> other);
	void swap(Optional<T>& other);

	void reset() throw();

	template <typename F>
	Optional<T> and_then(F f);
	template <typename F>
	Optional<T> and_then(F f) const;
	template <typename F>
	Optional<T> or_else(F f);
	template <typename F>
	Optional<T> or_else(F f) const;

	operator bool() const throw();
	bool has_value() const throw();
	T& value();
	const T& value() const;
	T& value_or(T& default_value);
	T& value_or(T& default_value) const;

private:
	T _value;
	bool _has_value;
};

} // namespace utils
