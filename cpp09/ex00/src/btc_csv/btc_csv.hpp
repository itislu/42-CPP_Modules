#pragma once

#include "BitcoinExchange.hpp"
#include "Csv.hpp"
#include <string>

namespace btc_csv {

struct BtcInserter {
	explicit BtcInserter(BitcoinExchange& b);

	void operator()(const Csv<2>& csv,
	                const std::string& date_str,
	                const std::string& exchange_rate_str) const;

	BitcoinExchange& btc; // NOLINT: Functor.
};

struct BtcQuerier {
	static const float max_query_amount /*= 1000*/;

	explicit BtcQuerier(const BitcoinExchange& b);

	void operator()(const Csv<2>& /*unused*/,
	                const std::string& date_str,
	                const std::string& query_amount_str) const;

	const BitcoinExchange& btc; // NOLINT: Functor.
};

template <typename RowFunction>
bool for_each_row(const std::string& filename,
                  const std::string& delim,
                  RowFunction row_fn);

} // namespace btc_csv

#include "for_each_row.tpp" // IWYU pragma: export
