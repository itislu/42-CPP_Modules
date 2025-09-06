#include "utils.hpp"
#include "Csv.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/format.hpp"
#include "parse.hpp"
#include <iostream>
#include <ostream>

namespace btc_csv {

Csv<2>::iterator skip_header(Csv<2>& csv)
{
	Csv<2>::iterator cur = csv.begin();
	if (cur == csv.end()) {
		return cur;
	}

	if (cur->has_value()) {
		try {
			(void)parse_date((*cur)->fields[0]);
			(void)parse_exchange_rate((*cur)->fields[1]);
			// Valid fields, so not a header.
			return cur;
		}
		catch (const ft::Exception&) {
			// Parse tests not successful. Valid row but not valid fields.
			std::cout << ft::log::info("skipping header: \"") << (*cur)->line
			          << "\"\n";
		}
	}
	else {
		log_line_warning(csv) << cur->error() << " - invalid header\n";
	}

	return ++cur;
}

std::ostream& log_line_warning(const Csv<2>& csv)
{
	return std::cerr << ft::log::warn() << csv.filename() << ":"
	                 << csv.cur_line_nbr() << ": ";
}

} // namespace btc_csv
