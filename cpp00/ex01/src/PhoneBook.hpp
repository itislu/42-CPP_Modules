#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
public:
	static const int max_contacts = 8;

	PhoneBook(void);
	~PhoneBook(void);

	void add(void);
	void search(void);

private:
	Contact _contacts[PhoneBook::max_contacts];
	int _contact_count;
	int _index_new_contact;

	void _print_contacts(void);
	bool _prompt_index(int &index) const;
	Contact &_index(const int i);
};

#endif
