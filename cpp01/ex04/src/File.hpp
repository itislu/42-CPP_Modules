#include <fstream>
#include <string>

class File {
public:
	File(const char* filename);

	bool read(std::string& content);
	bool write(const std::string& content);
	bool bad() const;
	void error() const;

private:
	std::ifstream _infile;
	std::ofstream _outfile;
	std::string _infile_name;
	std::string _outfile_name;
	std::string _error_message;
	int _infile_errno;
	int _outfile_errno;
};
