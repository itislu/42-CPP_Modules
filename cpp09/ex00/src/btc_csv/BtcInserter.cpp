#include "BitcoinExchange.hpp"
#include "Csv.hpp"
#include "btc_csv.hpp"
#include "detail/parse.hpp"
#include "detail/utils.hpp"
#include "libftpp/Optional.hpp"
#include <ctime>
#include <string>

namespace btc_csv {

BtcInserter::BtcInserter(BitcoinExchange& b)
    : btc(b)
{}

void BtcInserter::operator()(const Csv<2>& csv,
                             const std::string& date_str,
                             const std::string& exchange_rate_str) const
{
	const std::time_t date = detail::parse_date(date_str);
	const double rate = detail::parse_exchange_rate(exchange_rate_str);
	const ft::Optional<double> prev_rate = btc.insert(date, rate);

	if (prev_rate) {
		detail::log_line_warning(csv)
		    << "BitcoinExchange: duplicate entry for " << date_str
		    << (*prev_rate != rate ? " - replaced with new exchange rate\n"
		                           : "\n");
	}
}

} // namespace btc_csv
