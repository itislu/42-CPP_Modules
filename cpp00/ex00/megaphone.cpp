#include <iostream>
#include <locale>
#include <string>

int main()
{
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
    const std::ctype<wchar_t>& facet = std::use_facet<std::ctype<wchar_t> >(std::locale());

    std::wstring str = L"äëñaóűßδ*.";

    facet.toupper(&str[0], &str[0] + str.size());

    std::wcout << str << std::endl;

    return 0;
}
