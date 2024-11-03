#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
public:
	static void print_header();
	static void print_delim_top();
	static void print_delim_middle();
	static void print_delim_bottom();

	bool prompt_to_fill();
	void print_preview(const int index) const;
	void print_full() const;

	static const int display_width = 10;

private:
	static std::wstring _get_printable_str(const std::wstring& str);

	std::wstring _first_name;
	std::wstring _last_name;
	std::wstring _nickname;
	std::wstring _phone_number;
	std::wstring _darkest_secret;
};

#endif
