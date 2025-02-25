// NOLINTBEGIN(misc-use-anonymous-namespace)
// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)

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

static std::wstring concat_str_arr(char* arr[]);
static std::wstring convert_to_wstring(const char* mbs);
static size_t wcslen(const char* mbs);
static void str_toupper(std::wstring& wcs);

int main(int argc, char* argv[])
{
	std::wstring wcs = L"* LOUD AND UNBEARABLE FEEDBACK NOISE *";

	setlocale(LC_CTYPE, "");
	if (argc > 1) {
		wcs = concat_str_arr(&argv[1]);
		str_toupper(wcs);
	}
	if (!wcs.empty()) {
		std::wcout << wcs << '\n';
	}
	return 0;
}

static std::wstring concat_str_arr(char* arr[])
{
	std::wstring wcs;

	for (int i = 0; arr[i] != NULL; ++i) {
		wcs.append(convert_to_wstring(arr[i]));
	}
	return wcs;
}

static std::wstring convert_to_wstring(const char* mbs)
{
	size_t len = wcslen(mbs);
	std::wstring wcs;

	if (len != 0) {
		wcs.resize(len);
		mbstowcs(&wcs.at(0), mbs, len);
	}
	return wcs;
}

static size_t wcslen(const char* mbs)
{
	return mbstowcs(NULL, mbs, 0);
}

static void str_toupper(std::wstring& wcs)
{
	for (std::wstring::iterator it = wcs.begin(); it != wcs.end(); ++it) {
		*it = (wchar_t)towupper(*it);
	}
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
// NOLINTEND(misc-use-anonymous-namespace)
