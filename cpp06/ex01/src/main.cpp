// NOLINTBEGIN(readability-magic-numbers)

#include "Data.hpp"
#include "Serializer.hpp"
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdint.h>

int main()
{
	// Serializer serializer; // Not instantiable
	Data data = {"hello world", NULL, 42.42, 100};

	std::cout << std::setw(8) << std::left << "Before:" << &data << '\n';
	std::cout << std::setw(8) << std::left << "After:"
	          << Serializer::deserialize(Serializer::serialize(&data)) << '\n';
	std::cout << std::setw(8) << std::left << "Data:"
	          << *Serializer::deserialize(Serializer::serialize(&data)) << '\n';

	std::cout << '\n';

	const uintptr_t raw = Serializer::serialize(&data);
	const Data* ptr = Serializer::deserialize(raw);

	std::cout << std::setw(8) << std::left << "Raw:" << std::setbase(16) << "  "
	          << raw << std::setbase(10) << '\n';
	std::cout << std::setw(8) << std::left << "Ptr:" << ptr << '\n';
	std::cout << std::setw(8) << std::left << "Data:" << *ptr << '\n';

	std::cout << '\n';

	std::cout << std::setw(8) << std::left
	          << "NULL:" << Serializer::deserialize(Serializer::serialize(NULL))
	          << '\n';
}

// NOLINTEND(readability-magic-numbers)
