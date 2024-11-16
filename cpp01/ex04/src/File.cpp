#include "File.hpp"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

File::File(const char* filename) :
    _infile_name(filename),
    _outfile_name(this->_infile_name + ".replace"),
    _infile_errno(0),
    _outfile_errno(0)
{
	this->_infile.open(this->_infile_name.c_str(), std::ifstream::in);
	if (this->_infile.fail()) {
		this->_infile_errno = errno;
		return;
	}
	this->_outfile.open(this->_outfile_name.c_str(),
	                    std::ofstream::out | std::ofstream::trunc);
	if (this->_outfile.fail()) {
		this->_outfile_errno = errno;
		return;
	}
}

bool File::read(std::string& content)
{
	if (this->bad()) {
		return false;
	}
	std::stringstream buffer;
	buffer << this->_infile.rdbuf();
	if (this->_infile.fail()) {
		this->_infile_errno = errno;
		return false;
	}
	content = buffer.str();
	return true;
}

bool File::write(const std::string& content)
{
	if (this->bad()) {
		return false;
	}
	this->_outfile << content;
	if (this->_outfile.fail()) {
		this->_outfile_errno = errno;
		return false;
	}
	return true;
}

bool File::bad() const
{
	return this->_infile.fail() || this->_outfile.fail();
}

void File::error() const
{
	if (this->_infile_errno != 0) {
		std::cerr << this->_infile_name + ": " + strerror(this->_infile_errno)
		          << '\n';
	}
	if (this->_outfile_errno != 0) {
		std::cerr << this->_outfile_name + ": " + strerror(this->_outfile_errno)
		          << '\n';
	}
}
