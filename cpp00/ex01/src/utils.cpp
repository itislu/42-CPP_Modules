#include <cstdio>
#include <iostream>

bool prompt(const char *p, std::string &dest)
{
	while (std::cin.good()) {
		std::cout << p << ": ";
		if (!std::getline(std::cin, dest)) {
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
	std::cin.ignore();
	std::cin.clear();
	std::freopen("/dev/tty", "r", stdin);
	return false;
}

bool str_isdigit(std::string &str)
{
	for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
		if (!std::isdigit(*it)) {
			return false;
		}
	}
	return true;
}
