#include "BitcoinExchange.hpp"
#include "Csv.hpp"
#include "Date.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/format.hpp"
#include <cstddef>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

// What if duplicate date in data.csv? - Quit with a detailed error message.

/*
I would like to mostly use the same parsing for data.csv and input.

I want warning if ...
- header missing
  - (take format of first data line)
- different header than subject
- data format mismatch with header
- invalid date
- invalid date format
- invalid value (string)
- negative value
- too large value

Any warning should skip that line.
*/

static void fill_exchange(BitcoinExchange& btc, const std::string& data_file);
static void query_exchange(BitcoinExchange& btc, const std::string& query_file);
static std::time_t parse_date(const std::string& str);
template <typename T>
static T parse_value(const std::string& str);
template <typename T>
static T parse_amount(const std::string& str);

static const char* const default_data_file = "data.csv";
static const float max_query_amount = 1000;

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
int main(int argc, char* argv[])
try {
	if (argc < 2 || argc > 3) {
		std::cerr << "Usage: " << argv[0]
		          << " <input_file> [data_file=" << default_data_file << "]"
		          << '\n';
		return 1;
	}

	const std::string query_file(argv[1]);
	const std::string data_file(argc >= 3 ? argv[2] : default_data_file);
	BitcoinExchange btc;

	fill_exchange(btc, data_file);
	query_exchange(btc, query_file);

	return 0;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(e.what()) << '\n';
	return 2;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

static void fill_exchange(BitcoinExchange& btc, const std::string& data_file)
{
	std::cout << BOLD(UNDERLINE("Fill BitcoinExchange with " + data_file))
	          << '\n';

	Csv<2> csv(data_file);

	for (Csv<2>::iterator cur = csv.begin(), end = csv.end(); cur != end;
	     ++cur) {
		const std::size_t line_nbr = (*cur)[0].line_nbr;
		const std::string& date_str = (*cur)[0].data;
		const std::string& value_str = (*cur)[1].data;

		try {
			const std::time_t date = parse_date(date_str);
			const double value = parse_value<double>(value_str);
			const ft::Optional<double> prev_value = btc.insert(date, value);

			if (prev_value) {
				std::cerr << ft::log::warn() << data_file << ":" << line_nbr
				          << ": Duplicate entry for " << date_str
				          << (*prev_value != value
				                  ? " - replaced with new value"
				                  : "")
				          << '\n';
			}
		}
		catch (const std::logic_error& e) {
			std::cerr << ft::log::warn() << data_file << ":" << line_nbr << ": "
			          << e.what() << " - skipping line " << line_nbr << '\n';
		}
	}

	if (csv.cur_line_nbr() == 0) {
		std::cerr << ft::log::warn(data_file + " is empty") << '\n';
	}
}

static void query_exchange(BitcoinExchange& btc, const std::string& query_file)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE("Query BitcoinExchange with " + query_file))
	          << '\n';

	Csv<2> csv(query_file, '|');
	std::cout << std::fixed << std::setprecision(2);

	for (Csv<2>::iterator cur = csv.begin(), end = csv.end(); cur != end;
	     ++cur) {
		const std::size_t line_nbr = (*cur)[0].line_nbr;
		const std::string& date_str = (*cur)[0].data;
		const std::string& amount_str = (*cur)[1].data;

		try {
			const std::time_t date = parse_date(date_str);
			const float amount = parse_amount<float>(amount_str);
			const double value = btc.find(date) * amount;

			std::cout << ft::log::ok() << date_str << ": BTC " << amount_str
			          << " = " << value << '\n';
		}
		catch (const std::logic_error& e) {
			std::cerr << ft::log::warn() << query_file << ":" << line_nbr
			          << ": " << e.what() << " - skipping line " << line_nbr
			          << '\n';
		}
	}

	if (csv.cur_line_nbr() == 0) {
		std::cerr << ft::log::warn(query_file + " is empty") << '\n';
	}
	else {
		std::cout << ft::log::ok("Done") << '\n';
	}
}

static std::time_t parse_date(const std::string& str)
{
	std::string::size_type endpos = 0;
	const std::time_t date = Date::serialize(str, &endpos);
	if (endpos != str.length()) {
		throw std::invalid_argument("Excess characters in date column");
	}
	return date;
}

template <typename T>
static T parse_value(const std::string& str)
{
	std::string::size_type endpos = 0;
	const T value = ft::from_string<T>(str, &endpos);
	if (endpos != str.length()) {
		throw std::invalid_argument("Excess characters in value column");
	}
	return value;
}

template <typename T>
static T parse_amount(const std::string& str)
{
	const T amount = parse_value<T>(str);
	if (amount < 0) {
		throw std::invalid_argument("Negative query amount");
	}
	if (amount > max_query_amount) {
		throw std::invalid_argument("Too large query amount");
	}
	return amount;
}
