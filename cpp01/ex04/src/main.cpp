// NOLINTBEGIN(misc-use-anonymous-namespace)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

#include "File.hpp"
#include <cstdio>
#include <iostream>
#include <string>

enum error {
	ERROR_USAGE = 1,
	ERROR_FILE = 2
};

static std::string do_replace(const std::string& content,
							  const std::string& search,
							  const std::string& replace);

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr << "Usage: ./sed <filename> <search> <replace>" << '\n';
		return ERROR_USAGE;
	}
	File file(argv[1]);
	if (file.bad()) {
		file.error();
		return ERROR_FILE;
	}
	const std::string search(argv[2]);
	const std::string replace(argv[3]);

	std::string content;
	if (!file.read(content)) {
		file.error();
		return ERROR_FILE;
	}

	std::string result = do_replace(content, search, replace);

	if (!file.write(result)) {
		file.error();
		return ERROR_FILE;
	}
}

static std::string do_replace(const std::string& content,
							  const std::string& search,
							  const std::string& replace)
{
	std::string result;
	if (!search.empty()) {
		size_t start = 0;
		size_t end = 0;
		while ((end = content.find(search, end)) != std::string::npos) {
			result.append(content, start, end - start);
			result.append(replace);
			end += search.length();
			start = end;
		}
		result.append(content, start);
	}
	return result;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTEND(misc-use-anonymous-namespace)
