#pragma once

#include <ctime>
#include <map>

class BitcoinExchange {
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(BitcoinExchange other);
	~BitcoinExchange();

	/**
	 * @throws std::invalid_argument When trying to insert a negative value
	 * @throws std::invalid_argument When an entry with that date already exists
	 */
	void insert(std::time_t date, double value);
	/**
	 * @throws std::out_of_range When the database is empty or `date` is before
	 * the first entry in the database
	 */
	double find(std::time_t date) const;

	void swap(BitcoinExchange& other);

private:
	std::map<std::time_t /*date*/, double /*value*/> _db;
};
