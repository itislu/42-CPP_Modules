#include <cwctype>
#include <iostream>
#include <string>

class Megaphone {
 private:
  std::wstring _str;

 public:
  Megaphone(const std::wstring &s) : _str(s) {}

  void toUpper() {
    for (std::wstring::iterator it = this->_str.begin(); it != this->_str.end();
         ++it)
      *it = std::towupper(*it);
  }

  const std::wstring &get() const { return _str; }

  void print() const { std::wcout << _str << std::endl; }
};

int main(int argc, char *argv[]) {
  std::setlocale(LC_CTYPE, "");

  Megaphone megaphone(L"äëñaóűßδ*¤£¥.");

  megaphone.toUpper();
  megaphone.print();

  return 0;
}
