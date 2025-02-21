#pragma once

#include "utils/Exception.hpp"
#include <string>

namespace GradeException {

class AGradeException : public utils::Exception {
public:
	virtual ~AGradeException() throw() = 0;

	bool is_too_high() const;
	bool is_too_low() const;

	long delta() const;

protected:
	AGradeException(long delta,
	                const std::string& msg,
	                const std::string& where = "",
	                const std::string& who = "");
	AGradeException(const AGradeException& other);

private:
	AGradeException& operator=(const AGradeException& other);

	long _delta;
};

} // namespace GradeException
