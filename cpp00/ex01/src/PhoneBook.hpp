#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
public:
	PhoneBook();
	~PhoneBook();

	void add();
	void search();

	static const int max_contacts = 8;

private:
	void _print_contacts();
	bool _prompt_index(int& index) const;
	Contact& _index(const int i);

	Contact _contacts[PhoneBook::max_contacts];
	int _contact_count;
	int _index_new_contact;
};

#endif
