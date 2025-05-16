#include "BitcoinExchange.hpp"
#include "Date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/algorithm.hpp"
#include <ctime>
#include <map>
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

ft::Optional<double> BitcoinExchange::insert(std::time_t date, double rate)
{
	if (rate < 0) {
		throw ft::Exception("negative exchange rate", "BitcoinExchange");
	}
	const std::pair<std::map<std::time_t, double>::iterator, bool> result =
	    _db.insert(std::make_pair(date, rate));
	if (!result.second /*inserted?*/) {
		const double prev_value = (*result.first /*entry*/).second /*rate*/;
		(*result.first).second = rate;
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
		throw ft::Exception(_db.empty() ? "the database is empty"
		                                : "no data before "
		                                      + Date::str(_db.begin()->first),
		                    "BitcoinExchange");
	}
	// Closest lower entry
	return (--it)->second;
}

void BitcoinExchange::swap(BitcoinExchange& other) { ft::swap(_db, other._db); }
