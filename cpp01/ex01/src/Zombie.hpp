#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie { // NOLINT
public:
	Zombie();
	Zombie(const std::string& name);
	~Zombie();

	void announce();
	void set_name(const std::string& name);

private:
	std::string _name;
};

#endif
