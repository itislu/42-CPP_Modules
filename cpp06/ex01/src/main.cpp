// NOLINTBEGIN(readability-magic-numbers)

#include "Data.hpp"
#include "Serializer.hpp"
#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdint.h>
#include <string>

template <typename T>
static void
print_labeled(const std::string& label,
              const T& value,
              std::ios_base::fmtflags fmt = std::ios_base::fmtflags());

int main()
{
	// Serializer serializer; // Not instantiable
	Data data = {"hello world", NULL, 42.42, 100};

	print_labeled("Before", &data);
	print_labeled("After",
	              Serializer::deserialize(Serializer::serialize(&data)));
	print_labeled("Data",
	              *Serializer::deserialize(Serializer::serialize(&data)));

	std::cout << '\n';

	const uintptr_t raw = Serializer::serialize(&data);
	const Data* ptr = Serializer::deserialize(raw);

	print_labeled("Raw", raw, std::ios_base::hex | std::ios_base::showbase);
	print_labeled("Ptr", ptr);
	print_labeled("Data", *ptr);

	std::cout << '\n';

	print_labeled("NULL", Serializer::deserialize(Serializer::serialize(NULL)));
}

template <typename T>
static void print_labeled(const std::string& label,
                          const T& value,
                          std::ios_base::fmtflags fmt)
{
	const int label_width = 8;
	const std::ios_base::fmtflags fmt_backup = std::cout.flags();

	std::cout << std::setw(label_width) << std::left << label + ": ";
	std::cout.flags(fmt);
	std::cout << value;
	std::cout.flags(fmt_backup);
	std::cout << '\n';
}

// NOLINTEND(readability-magic-numbers)
