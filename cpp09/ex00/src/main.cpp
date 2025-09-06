#include "BitcoinExchange.hpp"
#include "btc_csv/btc_csv.hpp"
#include "libftpp/format.hpp"
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef DEFAULT_DATA_FILE
#	define DEFAULT_DATA_FILE "test_data/data.csv"
#endif

static void fill_exchange(BitcoinExchange& btc, const std::string& data_file);
static void query_exchange(BitcoinExchange& btc, const std::string& query_file);

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

	const bool had_data =
	    btc_csv::for_each_row(data_file, ",", btc_csv::BtcInserter(btc));
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
	btc_csv::for_each_row(query_file, " | ", btc_csv::BtcQuerier(btc));
}
