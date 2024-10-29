#include <cstdlib>
#include <iostream>
#include <string>

/**
 * mbs = multi byte string
 * wcs = wide char string
 */

static std::wstring concatStrArr(char *arr[]);
static std::wstring convertToWstring(const char *str);
static size_t mbslen(const char *str);
static void strToUpper(std::wstring &str);

int main(int argc, char *argv[])
{
	std::wstring str = L"* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	std::setlocale(LC_CTYPE, "");
	if (argc > 1) {
		str = concatStrArr(&argv[1]);
		strToUpper(str);
	}
	std::wcout << str << std::endl;
	return 0;
}

static std::wstring concatStrArr(char *arr[])
{
	std::wstring str;

	for (int i = 0; arr[i]; ++i) {
		str.append(convertToWstring(arr[i]));
	}
	return str;
}

static std::wstring convertToWstring(const char *str)
{
	size_t len;
	std::wstring wstr;

	len = mbslen(str);
	wstr.resize(len);
	std::mbstowcs(&wstr.at(0), str, len);
	return wstr;
}

static size_t mbslen(const char *str)
{
	return std::mbstowcs(NULL, str, 0);
}

static void strToUpper(std::wstring &str)
{
	for (std::wstring::iterator it = str.begin(); it != str.end(); ++it) {
		*it = std::towupper(*it);
	}
}
