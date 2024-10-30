#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "Contact.hpp"
#include <string>

class PhoneBook {
  public:
	static const int MAX_CONTACTS = 8;

	void add(void);
	void search(void);

	PhoneBook(void);
	~PhoneBook(void);

  private:
	Contact _contacts[PhoneBook::MAX_CONTACTS];
	int _contact_count;
	int _index_new_contact;

	bool _prompt_index(int &index);
	void _print_contacts(void);
	Contact &_index(int i);
};

#endif
