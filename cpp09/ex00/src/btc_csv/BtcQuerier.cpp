#include "BitcoinExchange.hpp"
#include "Csv.hpp"
#include "btc_csv.hpp"
#include "detail/parse.hpp"
#include "libftpp/format.hpp"
#include <ctime>
#include <iostream>
#include <string>

namespace btc_csv {

const float BtcQuerier::max_query_amount = 1000;

BtcQuerier::BtcQuerier(const BitcoinExchange& b)
    : btc(b)
{}

void BtcQuerier::operator()(const Csv<2>& /*unused*/,
                            const std::string& date_str,
                            const std::string& query_amount_str) const
{
	const std::time_t date = parse_date(date_str);
	const float amount = parse_query_amount(query_amount_str, max_query_amount);
	const double value = btc.find(date) * amount;

	std::cout << ft::log::ok() << date_str << ": BTC " << query_amount_str
	          << " = " << value << '\n';
}

} // namespace btc_csv
