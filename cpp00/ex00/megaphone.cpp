#include <cstdlib>
#include <cwctype>
#include <iostream>
#include <string>

class Megaphone
{
  private:
    std::wstring _str;

  public:
    Megaphone() : _str(L"* LOUD AND UNBEARABLE FEEDBACK NOISE *") {}

    Megaphone(const std::wstring &s) : _str(s) {}

    Megaphone(char *array[])
    {
        for (int i = 0; array[i]; i++)
            this->_str.append(_convertToWstring(array[i]));
    }

    void toUpper()
    {
        for (std::wstring::iterator it = this->_str.begin();
             it != this->_str.end(); ++it)
            *it = std::towupper(*it);
    }

    void print() const { std::wcout << _str << std::endl; }

  private:
    std::wstring _convertToWstring(const char *str)
    {
        size_t len = std::mbstowcs(NULL, str, 0);
        std::wstring wstr(len, L'\0');
        std::mbstowcs(&wstr[0], str, len);
        return wstr;
    }
};

int main(int argc, char *argv[])
{
    std::setlocale(LC_CTYPE, "");

    Megaphone megaphone;

    if (argc > 1)
        megaphone = Megaphone(&argv[1]);

    megaphone.toUpper();
    megaphone.print();

    return 0;
}
