#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum error {
	ERROR_USAGE = 1,
	ERROR_INFILE = 2,
	ERROR_OUTFILE = 3
};

int main(int argc, char* argv[])
{
	if (argc != 4) {
		std::cerr << "Usage: ./sed <filename> <search> <replace>" << '\n';
		return ERROR_USAGE;
	}
	std::string infile_name(*(argv + 1));
	std::string search(*(argv + 2));
	std::string replace(*(argv + 3));
	std::string outfile_name(infile_name + ".replace");

	std::ifstream infile(infile_name.c_str(), std::ifstream::in);
	if (!infile) {
		perror(infile_name.c_str());
		return ERROR_INFILE;
	}

	std::ofstream outfile(outfile_name.c_str(),
						  std::ofstream::out | std::ofstream::trunc);
	if (!outfile) {
		perror(outfile_name.c_str());
		return ERROR_OUTFILE;
	}

	std::stringstream buffer;
	buffer << infile.rdbuf();
	if (infile.fail()) {
		perror(infile_name.c_str());
		return ERROR_INFILE;
	}

	const std::string content(buffer.str());
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
	}

	outfile << result;
	if (outfile.fail()) {
		perror(outfile_name.c_str());
		return ERROR_OUTFILE;
	}
}
