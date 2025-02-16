// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#pragma once

#include <exception>
#include <string>

namespace GradeException {

class AGradeException : public std::exception {
public:
	virtual ~AGradeException() throw() = 0;

	const char* what() const throw();
	AGradeException& set_where(const std::string& where);
	AGradeException& set_who(const std::string& who);
	bool is_too_high() const;
	bool is_too_low() const;

	const std::string& msg() const;
	const std::string& where() const;
	const std::string& who() const;

protected:
	AGradeException(bool is_too_low,
	                const std::string& msg,
	                const std::string& where = "",
	                const std::string& who = "");

private:
	void _update_full_msg();

	bool _is_too_low;
	std::string _msg;
	std::string _where;
	std::string _who;
	std::string _full_msg;
};

class GradeTooHighException : public AGradeException {
public:
	GradeTooHighException(unsigned int grade,
	                      unsigned int required,
	                      const std::string& where = "",
	                      const std::string& who = "");
	GradeTooHighException(const AGradeException& other);
};

class GradeTooLowException : public AGradeException {
public:
	GradeTooLowException(unsigned int grade,
	                     unsigned int required,
	                     const std::string& where = "",
	                     const std::string& who = "");
	GradeTooLowException(const AGradeException& other);
};

} // namespace GradeException

// NOLINTEND(cppcoreguidelines-special-member-functions)
