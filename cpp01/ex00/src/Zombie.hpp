#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
	Zombie(std::string name);
	~Zombie(void);

	void announce(void);

private:
	Zombie(void);

	std::string _name;
};

#endif
