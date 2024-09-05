#include <cwctype>
#include <iostream>
#include <string>

void toUpper(std::wstring &str)
{
    for (std::wstring::iterator it = str.begin(); it != str.end(); ++it)
        *it = std::towupper(*it);
}

int main(int argc, char *argv[])
{
    std::setlocale(LC_CTYPE, "");

    std::wstring str = L"äëñaóűßδ*¤£¥.";
    toUpper(str);

    std::wcout << str << std::endl;
    return 0;
}
