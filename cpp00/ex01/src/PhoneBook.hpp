#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "Contact.hpp"
#include <string>

class PhoneBook {
  public:
	static const int MAX_CONTACTS = 8;

	PhoneBook(void);
	~PhoneBook(void);

	void add(void);
	void search(void);

  private:
	Contact _contacts[PhoneBook::MAX_CONTACTS];
	int _contact_count;
	int _index_new_contact;

	void _print_contacts(void);
	bool _prompt_index(int &index) const;
	Contact &_index(const int i);
};

#endif
