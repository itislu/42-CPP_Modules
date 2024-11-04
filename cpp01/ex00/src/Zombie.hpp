#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie { // NOLINT
public:
	Zombie(const std::string& name);
	~Zombie();

	void announce();

private:
	Zombie();

	std::string _name;
};

#endif
