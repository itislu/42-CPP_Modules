#include "BitcoinExchange.hpp"
#include "Csv.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/format.hpp"
#include "parse.hpp"
#include <cstddef>
#include <ctime>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef DEFAULT_DATA_FILE
#	define DEFAULT_DATA_FILE "test_data/data.csv"
#endif

static void fill_exchange(BitcoinExchange& btc, const std::string& data_file);
static void query_exchange(BitcoinExchange& btc, const std::string& query_file);
template <typename RowFn>
static bool for_each_row(const std::string& filename,
                         const std::string& delim,
                         RowFn row_fn);
struct RowInserter {
	explicit RowInserter(BitcoinExchange& b);
	void operator()(const Csv<2>& csv,
	                const std::string& date_str,
	                const std::string& rate_str) const;
	BitcoinExchange& btc; // NOLINT: Functor.
};
struct RowQuerier {
	explicit RowQuerier(BitcoinExchange& b);
	void operator()(const Csv<2>& /*unused*/,
	                const std::string& date_str,
	                const std::string& amount_str) const;
	BitcoinExchange& btc; // NOLINT: Functor.
};
static Csv<2>::iterator skip_header(Csv<2>& csv);
template <std::size_t Columns>
static std::ostream& log_line_warning(const Csv<Columns>& csv);

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv
int main(int argc, char* argv[])
try {
	if (argc < 2 || argc > 3) {
		std::cerr << "Usage: " << argv[0]
		          << " <input_file> [data_file=" DEFAULT_DATA_FILE "]\n";
		return 1;
	}

	const std::string query_file(argv[1]);
	const std::string data_file(argc >= 3 ? argv[2] : DEFAULT_DATA_FILE);
	BitcoinExchange btc;

	fill_exchange(btc, data_file);
	query_exchange(btc, query_file);

	return 0;
}
catch (const std::exception& e) {
	std::cerr << ft::log::error(e.what()) << '\n';
	return 2;
}
// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic): argv

static void fill_exchange(BitcoinExchange& btc, const std::string& data_file)
{
	std::cout << BOLD(UNDERLINE("Fill BitcoinExchange with " + data_file))
	          << '\n';

	const bool had_data = for_each_row(data_file, ",", RowInserter(btc));
	if (had_data) {
		std::cout << ft::log::ok("Done") << '\n';
	}
}

static void query_exchange(BitcoinExchange& btc, const std::string& query_file)
{
	std::cout << '\n'
	          << BOLD(UNDERLINE("Query BitcoinExchange with " + query_file))
	          << '\n';

	std::cout << std::fixed << std::setprecision(2);
	for_each_row(query_file, " | ", RowQuerier(btc));
}

template <typename RowFn>
static bool for_each_row(const std::string& filename,
                         const std::string& delim,
                         RowFn row_fn)
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

RowInserter::RowInserter(BitcoinExchange& b)
    : btc(b)
{}

void RowInserter::operator()(const Csv<2>& csv,
                             const std::string& date_str,
                             const std::string& rate_str) const
{
	const std::time_t date = parse_date(date_str);
	const double rate = parse_rate(rate_str);
	const ft::Optional<double> prev_rate = btc.insert(date, rate);

	if (prev_rate) {
		log_line_warning(csv)
		    << "BitcoinExchange: duplicate entry for " << date_str
		    << (*prev_rate != rate ? " - replaced with new exchange rate\n"
		                           : "\n");
	}
}

RowQuerier::RowQuerier(BitcoinExchange& b)
    : btc(b)
{}

void RowQuerier::operator()(const Csv<2>& /*unused*/,
                            const std::string& date_str,
                            const std::string& amount_str) const
{
	const float max_query_amount = 1000;

	const std::time_t date = parse_date(date_str);
	const float amount = parse_amount(amount_str, max_query_amount);
	const double value = btc.find(date) * amount;

	std::cout << ft::log::ok() << date_str << ": BTC " << amount_str << " = "
	          << value << '\n';
}

/**
 * Detects if a header needs to be skipped or not.
 */
static Csv<2>::iterator skip_header(Csv<2>& csv)
{
	Csv<2>::iterator cur = csv.begin();
	if (cur == csv.end()) {
		return cur;
	}

	if (cur->has_value()) {
		try {
			(void)parse_date((*cur)->fields[0]);
			(void)parse_rate((*cur)->fields[1]);
			// Valid fields, so not a header.
			return cur;
		}
		catch (const ft::Exception&) {
			// EMPTY: Parse tests not successful.
			// Valid row but not valid fields.
		}
		std::cout << ft::log::info("skipping header: \"") << (*cur)->line
		          << "\"\n";
	}
	else {
		log_line_warning(csv) << cur->error() << " - invalid header\n";
	}

	return ++cur;
}

template <std::size_t Columns>
static std::ostream& log_line_warning(const Csv<Columns>& csv)
{
	return std::cerr << ft::log::warn() << csv.filename() << ":"
	                 << csv.cur_line_nbr() << ": ";
}
