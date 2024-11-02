#include <string>

class Zombie {
  public:
	Zombie(std::string name);
	~Zombie(void);

	void announce(void);

  private:
	std::string _name;

	Zombie(void);
};
