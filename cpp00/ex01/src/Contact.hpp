#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
  public:
	static const int DISPLAY_WIDTH = 10;

	std::wstring first_name;
	std::wstring last_name;
	std::wstring nickname;
	std::wstring phone_number;
	std::wstring darkest_secret;

	bool prompt_to_fill(void);
	void print(int index);
	void print_full(void);
	static void print_header(void);
	static void print_delim(void);

  private:
	static std::wstring _get_printable_str(std::wstring &str);
};

#endif
