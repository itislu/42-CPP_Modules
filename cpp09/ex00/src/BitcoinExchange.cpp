#include "BitcoinExchange.hpp"
#include "date.hpp"
#include "libftpp/Exception.hpp"
#include "libftpp/Optional.hpp"
#include "libftpp/algorithm.hpp"
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

ft::Optional<BitcoinExchange::mapped_type>
BitcoinExchange::insert(key_type date, mapped_type rate)
{
	const std::pair<DateRateMap_::iterator, bool> result =
	    _db.insert(std::make_pair(date, rate));
	const bool is_inserted = result.second;

	if (!is_inserted) {
		const DateRateMap_::iterator& entry = result.first;
		const mapped_type prev_rate = entry->second;
		entry->second = rate;
		return prev_rate;
	}
	return ft::nullopt;
}

BitcoinExchange::mapped_type BitcoinExchange::find(key_type date) const
{
	DateRateMap_::const_iterator it = _db.lower_bound(date);
	// Exact match.
	if (it != _db.end() && it->first == date) {
		return it->second;
	}
	// No lower entry.
	if (it == _db.begin()) {
		throw ft::Exception(_db.empty()
		                        ? "database is empty"
		                        : "no data before "
		                              + date::deserialize(_db.begin()->first),
		                    "BitcoinExchange");
	}
	// Closest lower entry.
	return (--it)->second;
}

void BitcoinExchange::swap(BitcoinExchange& other) { ft::swap(_db, other._db); }
