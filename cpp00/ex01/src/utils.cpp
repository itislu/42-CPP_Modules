#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

bool prompt(const wchar_t* p, std::wstring& dest)
{
	while (std::wcin.good()) {
		std::wcout << p << L": ";
		if (!std::getline(std::wcin, dest)) {
			std::wcout << '\n';
			break;
		}
		if (dest.empty()) {
			std::wcout << p << L" cannot be empty!" << '\n';
		}
		else {
			return true;
		}
	}
	std::wcin.ignore();
	std::wcin.clear();
	freopen("/dev/tty", "r", stdin);
	return false;
}

bool str_isdigit(std::wstring& str)
{
	for (std::wstring::iterator it = str.begin(); it != str.end(); ++it) {
		if (!(bool)std::isdigit(*it)) {
			return false;
		}
	}
	return true;
}
