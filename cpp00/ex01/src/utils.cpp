#include <cstdio>
#include <iostream>

bool prompt(const char *p, std::wstring &dest)
{
	while (std::wcin.good()) {
		std::cout << p << ": ";
		if (!std::getline(std::wcin, dest)) {
			std::cout << std::endl;
			break;
		}
		else if (dest.length() == 0) {
			std::cout << p << " cannot be empty!" << std::endl;
		}
		else {
			return true;
		}
	}
	std::wcin.ignore();
	std::wcin.clear();
	std::freopen("/dev/tty", "r", stdin);
	return false;
}

bool str_isdigit(std::wstring &str)
{
	for (std::wstring::iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isdigit(*it)) {
			return false;
		}
	}
	return true;
}
