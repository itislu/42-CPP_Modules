#pragma once

#include "libftpp/Optional.hpp"
#include <ctime>
#include <map>

class BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(BitcoinExchange other);
	~BitcoinExchange();

	/**
	 * @throws std::invalid_argument When trying to insert a negative exchange
	 * rate
	 *
	 * @returns A `ft::Optional<double>` containing the replaced exchange rate,
	 * or an empty `ft::Optional` if no previous exchange rate existed for that
	 * date
	 */
	ft::Optional<double> insert(std::time_t date, double rate);
	/**
	 * @throws std::out_of_range When the database is empty or `date` is before
	 * the first entry in the database
	 */
	double find(std::time_t date) const;

	void swap(BitcoinExchange& other);

private:
	std::map<std::time_t /*date*/, double /*rate*/> _db;
};
