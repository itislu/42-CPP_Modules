#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
public:
	enum Level {
		DEBUG,
		INFO,
		WARNING,
		ERROR,
		UNKNOWN
	};

	void complain(std::string level);

private:
	static void _debug();
	static void _info();
	static void _warning();
	static void _error();
	static Harl::Level _index(const std::string& level);

	static const int _num_levels = 4;
	static const std::string _levels[Harl::_num_levels];
};

#endif
