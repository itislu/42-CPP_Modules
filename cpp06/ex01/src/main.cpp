// NOLINTBEGIN(readability-magic-numbers)
// NOLINTBEGIN(hicpp-signed-bitwise)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)

#include "Data.hpp"
#include "Serializer.hpp"
#include "libftpp/common.hpp"
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
static void reinterpret_cast_example();

int main()
{
	// Serializer serializer; // Not instantiable
	Data data = {"hello world", NULL, 42.42, 100};

	{
		std::cout << BOLD("serialize -> deserialize:") << '\n';

		print_labeled("Before", &data);
		print_labeled("After",
		              Serializer::deserialize(Serializer::serialize(&data)));
		print_labeled("Data",
		              *Serializer::deserialize(Serializer::serialize(&data)));
	}
	{
		std::cout << '\n' << BOLD("raw and pointer values:") << '\n';

		const uintptr_t raw = Serializer::serialize(&data);
		const Data* ptr = Serializer::deserialize(raw);

		print_labeled("Raw", raw, std::ios_base::hex | std::ios_base::showbase);
		print_labeled("Ptr", ptr);
		print_labeled("Data", *ptr);
	}
	{
		std::cout << '\n'
		          << BOLD("serialize -> deserialize with NULL:") << '\n';

		print_labeled("NULL",
		              Serializer::deserialize(Serializer::serialize(NULL)));
	}
	std::cout << "\n--------------------------------------------\n" << '\n';

	std::cout << BOLD("reinterpret_cast example:") << '\n';
	reinterpret_cast_example();
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

static void reinterpret_cast_example()
{
	struct Bytefield {
		unsigned char byte0;
		unsigned char byte1;
		unsigned char byte2;
		unsigned char byte3;
	};

	Bytefield bytefield = {0, 0, 0, 1 << 7};

	std::cout << "byte0: " << static_cast<int>(bytefield.byte0)
	          << ",  byte1: " << static_cast<int>(bytefield.byte1)
	          << ",  byte2: " << static_cast<int>(bytefield.byte2)
	          << ",  byte3: " << static_cast<int>(bytefield.byte3) << '\n';

	std::cout << "Bytefield -> unsigned int: "
	          << *reinterpret_cast<unsigned int*>(&bytefield) << '\n';
}

// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
// NOLINTEND(hicpp-signed-bitwise)
// NOLINTEND(readability-magic-numbers)
