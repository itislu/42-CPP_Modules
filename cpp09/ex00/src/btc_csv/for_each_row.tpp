#pragma once

#include "Csv.hpp"
#include "btc_csv.hpp"
#include "detail/utils.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/format.hpp"
#include <iostream>
#include <string>

namespace btc_csv {

template <typename RowFunction>
bool for_each_row(const std::string& filename,
                  const std::string& delim,
                  RowFunction row_fn)
{
	Csv<2> csv(filename, delim);
	bool has_data = false;

	for (Csv<2>::iterator cur = skip_header(csv), end = csv.end(); cur != end;
	     ++cur) {
		try {
			if (!cur->has_value()) {
				throw ft::Exception(cur->error(), "Csv");
			}
			has_data = true;
			row_fn(const_cast<const Csv<2>&>(csv),
			       (*cur)->fields[0],
			       (*cur)->fields[1]);
		}
		catch (const ft::Exception& e) {
			log_line_warning(csv) << e.what() << " - skipping line "
			                      << csv.cur_line_nbr() << '\n';
		}
	}

	if (csv.cur_line_nbr() == 0) {
		std::cerr << ft::log::warn(filename + " is empty") << '\n';
	}
	else if (!has_data) {
		std::cerr << ft::log::warn(filename + " has no data") << '\n';
	}
	return has_data;
}

} // namespace btc_csv
