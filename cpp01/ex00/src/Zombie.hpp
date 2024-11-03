#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
	Zombie(std::string name);
	~Zombie();

	void announce();

private:
	Zombie();

	std::string _name;
};

#endif
