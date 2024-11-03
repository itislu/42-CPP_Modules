#include <iostream>
#include <string>

int main()
{
	std::string string("HI THIS IS BRAIN");
	std::string* stringPTR = &string;
	std::string& stringREF = string;

	std::cout << "ADDRESSES:" << "\n";
	std::cout << &string << "\n";
	std::cout << stringPTR << "\n";
	std::cout << &stringREF << "\n\n";

	std::cout << "VALUES:" << "\n";
	std::cout << string << "\n";
	std::cout << *stringPTR << "\n";
	std::cout << stringREF << "\n";
}
