#pragma once

#include "Csv.hpp"
#include <ostream>

namespace btc_csv {

/**
 * Detects if a header needs to be skipped or not.
 */
Csv<2>::iterator skip_header(Csv<2>& csv);

std::ostream& log_line_warning(const Csv<2>& csv);

} // namespace btc_csv
