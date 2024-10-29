#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "Contact.hpp"
#include <string>

#define MAX_CONTACTS 8

class PhoneBook {
  public:
	void add(void);
	void search(void);

	PhoneBook(void);
	~PhoneBook(void);

  private:
	Contact _contacts[8];
	int _contact_count;
	int _index_new_contact;

	void _print_contacts(void);
	Contact &_index(int i);
};

#endif
