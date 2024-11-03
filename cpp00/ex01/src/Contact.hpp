#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
  public:
	static const int display_width = 10;

	static void print_header(void);
	static void print_delim_top(void);
	static void print_delim_middle(void);
	static void print_delim_bottom(void);

	bool prompt_to_fill(void);
	void print_preview(const int index) const;
	void print_full(void) const;

  private:
	std::wstring _first_name;
	std::wstring _last_name;
	std::wstring _nickname;
	std::wstring _phone_number;
	std::wstring _darkest_secret;

	static std::wstring _get_printable_str(const std::wstring &str);
};

#endif
