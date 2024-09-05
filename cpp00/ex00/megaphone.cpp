#include <cctype>
#include <iostream>
#include <string>

void print_uppercase(std::string str)
{
    std::string::iterator it;

    for (it = str.begin(); it != str.end(); it++)
        std::cout << static_cast<char>(toupper(static_cast<unsigned char>(*it)));
}

int main(int argc, char* argv[])
{
    if (argc == 1)
	{
        print_uppercase("* LOUD AND UNBEARABLE FEEDBACK NOISE *");
	}
    else
	{
		for (int i = 1; argv[i]; i++)
		{
			print_uppercase(argv[i]);
			std::cout << " ";
		}
	}
    std::cout << std::endl;
}
