#include <clocale>
#include <cstdlib>
#include <cwchar>
#include <cwctype>
#include <iostream>
#include <string>

/**
 * mbs = multi byte string
 * wcs = wide char string
 */

static std::wstring concatStrArr(char *arr[]);
static std::wstring convertToWstring(const char *mbs);
static size_t wcslen(const char *mbs);
static void strToUpper(std::wstring &wcs);

int main(int argc, char *argv[])
{
	std::wstring wcs = L"* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	std::setlocale(LC_CTYPE, "");
	if (argc > 1) {
		wcs = concatStrArr(&argv[1]);
		strToUpper(wcs);
	}
	if (wcs.length()) {
		std::wcout << wcs << std::endl;
	}
	return 0;
}

static std::wstring concatStrArr(char *arr[])
{
	std::wstring wcs;

	for (int i = 0; arr[i]; ++i) {
		wcs.append(convertToWstring(arr[i]));
	}
	return wcs;
}

static std::wstring convertToWstring(const char *mbs)
{
	size_t len;
	std::wstring wcs;

	len = wcslen(mbs);
	if (len) {
		wcs.resize(len);
		std::mbstowcs(&wcs.at(0), mbs, len);
	}
	return wcs;
}

static size_t wcslen(const char *mbs)
{
	return std::mbstowcs(NULL, mbs, 0);
}

static void strToUpper(std::wstring &wcs)
{
	for (std::wstring::iterator it = wcs.begin(); it != wcs.end(); ++it) {
		*it = std::towupper(*it);
	}
}
