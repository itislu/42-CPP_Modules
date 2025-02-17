#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", grade_to_sign, grade_to_sign, target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other)
{}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

ShrubberyCreationForm&
ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	AForm::operator=(other);
	return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const
{
	std::ofstream file;

	AForm::execute(executor);
	file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	file.open((target() + "_shrubbery").c_str(),
	          executions() <= 1 ? std::ios::trunc : std::ios::app);
	file << "\n\
              _{\\ _{\\{\\/}/}/}__\n\
             {/{/\\}{/{/\\}(\\}{/\\} _\n\
            {/{/\\}{/{/\\}(_)\\}{/{/\\}  _\n\
         {\\{/(\\}\\}{/{/\\}\\}{/){/\\}\\} /\\}\n\
        {/{/(_)/}{\\{/)\\}{\\(_){/}/}/}/}\n\
       _{\\{/{/{\\{/{/(_)/}/}/}{\\(/}/}/}\n\
      {/{/{\\{\\{\\(/}{\\{\\/}/}{\\}(_){\\/}\\}\n\
      _{\\{/{\\{/(_)\\}/}{/{/{/\\}\\})\\}{/\\}\n\
     {/{/{\\{\\(/}{/{\\{\\{\\/})/}{\\(_)/}/}\\}\n\
      {\\{\\/}(_){\\{\\{\\/}/}(_){\\/}{\\/}/})/}\n\
       {/{\\{\\/}{/{\\{\\{\\/}/}{\\{\\/}/}\\}(_)\n\
      {/{\\{\\/}{/){\\{\\{\\/}/}{\\{\\(/}/}\\}/}\n\
       {/{\\{\\/}(_){\\{\\{\\(/}/}{\\(_)/}/}\\}\n\
         {/({/{\\{/{\\{\\/}(_){\\/}/}\\}/}(\\}\n\
          (_){/{\\/}{\\{\\/}/}{\\{\\)/}/}(_)\n\
            {/{/{\\{\\/}{/{\\{\\{\\(_)/}\n\
             {/{\\{\\{\\/}/}{\\{\\\\}/}\n\
              {){/ {\\/}{\\/} \\}\\}\n\
              (_)  \\.-'.-/\n\
          __...--- |'-.-'| --...__\n\
   _...--'   .-'   |'-.-'|  ' -.  ''--..__\n\
 -'    ' .  . '    |.'-._| '  . .  '   \n\
 .  '-  '    .--'  | '-.'|    .  '  . '\n\
          ' ..     |'-_.-|\n\
  .  '  .       _.-|-._ -|-._  .  '  .\n\
              .'   |'- .-|   '.\n\
  ..-'   ' .  '.   `-._.-'   .'  '  - .\n\
   .-' '        '-._______.-'     '  .\n\
        .      -'\n\
    .       .        .    ' '-.\n";

	std::cout << target() << " got some" << (executions() > 1 ? " more" : "")
	          << " shrubbery" << '\n';
}
