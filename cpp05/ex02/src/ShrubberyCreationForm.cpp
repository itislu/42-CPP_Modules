#include "ShrubberyCreationForm.hpp"
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Grade.hpp"
#include <fstream>
#include <string>

const Grade ShrubberyCreationForm::grade_to_sign(145);
const Grade ShrubberyCreationForm::grade_to_exec(137);

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm",
            grade_to_sign.get(),
            grade_to_sign.get(),
            target)
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
	file.open((target() + "_shrubbery").c_str());
	file << "\
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
}
