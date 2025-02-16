// NOLINTBEGIN(cppcoreguidelines-special-member-functions)

#pragma once

#include <exception>
#include <string>

namespace GradeException {

class AGradeException : public std::exception {
public:
	virtual ~AGradeException() throw() = 0;

	const char* what() const throw();
	AGradeException& set_who(const std::string& who);
	AGradeException& set_where(const std::string& where);
	bool is_too_high() const;
	bool is_too_low() const;

	const std::string& msg() const;
	const std::string& who() const;
	const std::string& where() const;

protected:
	AGradeException(bool is_too_low,
	                const std::string& msg,
	                const std::string& who = "",
	                const std::string& where = "");

private:
	void _update_full_msg();

	bool _is_too_low;
	std::string _msg;
	std::string _who;
	std::string _where;
	std::string _full_msg;
};

class GradeTooHighException : public AGradeException {
public:
	GradeTooHighException(unsigned int grade,
	                      unsigned int required,
	                      const std::string& who = "",
	                      const std::string& where = "");
	GradeTooHighException(const AGradeException& other);
};

class GradeTooLowException : public AGradeException {
public:
	GradeTooLowException(unsigned int grade,
	                     unsigned int required,
	                     const std::string& who = "",
	                     const std::string& where = "");
	GradeTooLowException(const AGradeException& other);
};

} // namespace GradeException

// NOLINTEND(cppcoreguidelines-special-member-functions)
