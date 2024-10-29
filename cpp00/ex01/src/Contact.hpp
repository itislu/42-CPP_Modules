#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
  public:
	std::string first_name;
	std::string last_name;
	std::string nickname;
	std::string phone_number;
	std::string darkest_secret;

	bool prompt_to_fill(void);
	void print(int index);
	void print_full(void);
	static void print_header(void);
	static void print_delim(void);

  private:
};

#endif
