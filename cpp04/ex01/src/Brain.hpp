#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>

class Brain {
public:
	Brain();
	Brain(const Brain& other);
	virtual ~Brain();

	Brain& operator=(const Brain& other);

	static const int brain_size = 100;

private:
	std::string _ideas[Brain::brain_size];
};

#endif
