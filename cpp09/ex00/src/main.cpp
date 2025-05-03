#include "Csv.hpp"
#include "libftpp/format.hpp"
#include <exception>
#include <iostream>

// What if duplicate date in data.csv? - Quit with a detailed error message.

/*
I would like to mostly use the same parsing for data.csv and input.

I want warning if ...
- header missing
  - (take format of first data line)
- different header than subject
- data format mismatch with header
- invalid date
- invalid date format
- invalid value (string)
- negative value
- too large value

Any warning should skip that line.
*/

template class Csv<2>;

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
int main(int argc, char* argv[])
try {
	if (argc < 2 || argc > 3) {
		std::cerr << "Usage: " << argv[0]
		          << " <input_file> [data_file=data.csv]" << '\n';
		return 1;
	}

	Csv<2> csv(argv[1], '|');
	for (Csv<2>::iterator cur = csv.begin(), end = csv.end(); cur != end;
	     ++cur) {
		std::cout << (*cur)[0] << ", " << (*cur)[1] << '\n';
	}
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(BOLD("Unexpected exception: ") + e.what())
	          << '\n';
	return 2;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
