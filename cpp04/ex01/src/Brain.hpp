#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <ostream>
#include <string>

class Brain {
public:
	Brain();
	Brain(const Brain& other);
	~Brain();

	Brain& operator=(const Brain& other);

	void add_idea(const std::string& idea);
	std::string get_idea(int index) const;

	static const int brain_size = 100;

private:
	std::string _ideas[Brain::brain_size];
	int _index;
};

#endif
