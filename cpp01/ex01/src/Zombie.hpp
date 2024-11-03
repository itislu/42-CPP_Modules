#include <string>

class Zombie {
  public:
	Zombie(void);
	Zombie(std::string name);
	~Zombie(void);

	void announce(void);
	void set_name(std::string name);

  private:
	std::string _name;

};
