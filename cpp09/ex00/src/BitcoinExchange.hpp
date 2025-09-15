#pragma once

#include "libftpp/Optional.hpp"
#include <ctime>
#include <map>

class BitcoinExchange {
public:
	typedef std::time_t key_type;
	typedef double mapped_type;

	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(BitcoinExchange other);
	~BitcoinExchange();

	/**
	 * @return A `ft::Optional<BitcoinExchange::mapped_type>` containing the
	 * replaced exchange rate, or an empty `ft::Optional` if no previous
	 * exchange rate existed for that date
	 */
	ft::Optional<mapped_type> insert(key_type date, mapped_type rate);
	/**
	 * @throws ft::Exception When the database is empty or `date` is before the
	 * first entry in the database
	 */
	mapped_type find(key_type date) const;

	void swap(BitcoinExchange& other);

private:
	typedef std::map<key_type /*date*/, mapped_type /*rate*/> DateRateMap_;

	DateRateMap_ _db;
};
