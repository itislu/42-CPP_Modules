// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
// NOLINTBEGIN(hicpp-signed-bitwise)
// NOLINTBEGIN(readability-magic-numbers)

#include "Data.hpp"
#include "Serializer.hpp"
#include "libftpp/common.hpp"
#include "libftpp/log.hpp"
#include <cstddef>
#include <exception>
#include <iomanip>
#include <ios>
#include <iostream>
#include <new> // IWYU pragma: keep
#include <stdint.h>
#include <string>

template <typename T>
static void print_labeled(const std::string& label,
                          const T& value,
                          std::ios::fmtflags fmt = std::ios::fmtflags());
static void bytefield_example();
static void float_example();
template <typename T>
static void print_binary(T val);
static void delete_example();
static size_t unsafe_get_array_cookie(void* ptr);

int main()
try {
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

		print_labeled("Raw", raw, std::ios::hex | std::ios::showbase);
		print_labeled("Ptr", ptr);
		print_labeled("Data", *ptr);
	}
	{
		std::cout << '\n'
		          << BOLD("serialize -> deserialize with NULL:") << '\n';

		print_labeled("NULL",
		              Serializer::deserialize(Serializer::serialize(NULL)));
	}
	std::cout << '\n'
	          << BOLD("--------------------------------------------") << "\n\n";

	std::cout << BOLD("REINTERPRET_CAST EXAMPLES:") << '\n';
	bytefield_example();
	float_example();
	delete_example();
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Exception: ") + e.what()) << '\n';
	return 1;
}

template <typename T>
static void
print_labeled(const std::string& label, const T& value, std::ios::fmtflags fmt)
{
	const int label_width = 8;
	const std::ios::fmtflags fmt_backup = std::cout.flags();

	std::cout << std::setw(label_width) << std::left << label + ": ";
	std::cout.flags(fmt);
	std::cout << value;
	std::cout.flags(fmt_backup);
	std::cout << '\n';
}

static void bytefield_example()
{
	std::cout << '\n' << BOLD("Bytefield:") << '\n';

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

	const unsigned int i = *reinterpret_cast<unsigned int*>(&bytefield);
	std::cout << "Bytefield -> unsigned int: " << i << '\n';
	std::cout << "in binary: ", print_binary(i);
}

static void float_example()
{
	std::cout << '\n' << BOLD("Float Representation:") << '\n';

	const float f = 2.5;

	const int sc = static_cast<int>(f);
	const int rc = *reinterpret_cast<const int*>(&f);

	std::cout << "static_cast:      " << sc << '\n';
	std::cout << "reinterpret_cast: " << rc << '\n';
	std::cout << "float in binary:  ", print_binary(f);
}

template <typename T>
static void print_binary(T val)
{
	const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&val);
	std::string binary;

	for (unsigned int byte = 0; byte < sizeof(T); ++byte) {
		for (unsigned int i = 0; i < 8; ++i) {
			binary.insert(0, 1, (((*ptr >> i) & 1) ? '1' : '0'));
		}
		++ptr;
	}
	std::cout << "0b" + binary << '\n';
}

// NOLINTBEGIN
static void delete_example()
{
	std::cout << '\n' << BOLD("operator delete[]:") << '\n';

	class A {
	public:
		A()
		    : _ptr(new char[42]),
		      _i()
		{}
		~A() { (void)_i, delete[] _ptr; }

	private:
		char* _ptr;
		int _i;
	};

	const unsigned int amount = 10;
	A* array = new A[amount];

	std::cout << "size of A: " << sizeof(A) << '\n';
	std::cout << "newed size: " << unsafe_get_array_cookie(array) << '\n';

	/* Correct */
	delete[] array;

	/* Invalid free */
	// delete array;

	/* Segmentation fault (no object with destructor at that address) */
	// delete (reinterpret_cast<size_t*>(array) - 1);

	/* No segmentation fault (manual operator delete[]) */
	// for (unsigned int i = 0; i < amount; ++i) {
	// 	array[i].~A();
	// }
	// operator delete(reinterpret_cast<size_t*>(array) - 1);
}
// NOLINTEND

static size_t unsafe_get_array_cookie(void* ptr)
#if defined(__clang__)
    __attribute__((no_sanitize("address")))
#endif
{
	return *(reinterpret_cast<size_t*>(ptr) - 1);
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(hicpp-signed-bitwise)
// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
