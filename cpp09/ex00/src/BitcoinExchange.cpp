#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include "libftpp/Optional.hpp"
#include <algorithm>
#include <ctime>
#include <map>
#include <stdexcept>
#include <utility>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
    : _db(other._db)
{}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange other)
{
	swap(other);
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

ft::Optional<double> BitcoinExchange::insert(std::time_t date, double value)
{
	if (value < 0) {
		throw std::invalid_argument("Negative value");
	}
	const std::pair<std::map<std::time_t, double>::iterator, bool> result =
	    _db.insert(std::make_pair(date, value));
	if (!result.second /*inserted?*/) {
		const double prev_value = (*result.first /*entry*/).second /*value*/;
		(*result.first).second = value;
		return prev_value;
	}
	return ft::nullopt;
}

double BitcoinExchange::find(std::time_t date) const
{
	std::map<std::time_t, double>::const_iterator it = _db.lower_bound(date);
	// Exact match
	if (it != _db.end() && it->first == date) {
		return it->second;
	}
	// No lower entry
	if (it == _db.begin()) {
		throw std::out_of_range(
		    "BitcoinExchange: "
		    + (_db.empty()
		           ? "The database is empty"
		           : "No data before " + Date::str(_db.begin()->first)));
	}
	// Closest lower entry
	return (--it)->second;
}

void BitcoinExchange::swap(BitcoinExchange& other)
{
	using std::swap;
	swap(_db, other._db);
}
