#include <cstddef>
#include <string>

class Harl {
public:
	Harl();

	void complain(std::string level);

private:
	static void debug();
	static void info();
	static void warning();
	static void error();

	static size_t _index(std::string level);

	static const int _num_levels = 4;
	static void (*_complaints[Harl::_num_levels])();

	static const std::string _levels[Harl::_num_levels];
	static size_t _max_len;
	static std::string _lookup;
};
