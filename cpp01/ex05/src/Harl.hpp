#include <cstddef>
#include <string>

class Harl {
public:
	Harl();

	void complain(std::string level);

private:
	static void _debug();
	static void _info();
	static void _warning();
	static void _error();
	static size_t _index(const std::string& level);

	static const int _num_levels = 4;
	static const std::string _levels[Harl::_num_levels];
	static void (*_complaints[Harl::_num_levels])();
	static size_t _max_len;
	static std::string _lookup;
};
