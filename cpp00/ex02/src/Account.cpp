#include "Account.hpp"
#include <ctime>
#include <iostream>

int Account::_nbAccounts;
int Account::_totalAmount;
int Account::_totalNbDeposits;
int Account::_totalNbWithdrawals;

static const char DELIM = ';';

int Account::getNbAccounts(void)
{
	return Account::_nbAccounts;
}

int Account::getTotalAmount(void)
{
	return Account::_totalAmount;
}

int Account::getNbDeposits(void)
{
	return Account::_totalNbDeposits;
}

int Account::getNbWithdrawals(void)
{
	return Account::_totalNbWithdrawals;
}

void Account::displayAccountsInfos(void)
{
	Account::_displayTimestamp();
	std::cout << " "
			  << "accounts:" << Account::getNbAccounts() << DELIM
			  << "total:" << Account::getTotalAmount() << DELIM
			  << "deposits:" << Account::getNbDeposits() << DELIM
			  << "withdrawals:" << Account::getNbWithdrawals() << std::endl;
}

Account::Account(int initial_deposit) :
	_accountIndex(Account::_nbAccounts),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0)
{
	Account::_displayTimestamp();
	std::cout << " "
			  << "index:" << this->_accountIndex << DELIM
			  << "amount:" << this->_amount << DELIM << "created" << std::endl;
	Account::_nbAccounts++;
	Account::_totalAmount += this->_amount;
}

Account::~Account(void)
{
	Account::_displayTimestamp();
	std::cout << " "
			  << "index:" << this->_accountIndex << DELIM
			  << "amount:" << this->_amount << DELIM << "closed" << std::endl;
}

void Account::makeDeposit(int deposit)
{
	int p_amount = this->_amount;

	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	Account::_displayTimestamp();
	std::cout << " "
			  << "index:" << this->_accountIndex << DELIM
			  << "p_amount:" << p_amount << DELIM
			  << "deposit:" << deposit << DELIM
			  << "amount:" << this->_amount << DELIM
			  << "nb_deposits:" << this->_nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
	int p_amount = this->_amount;

	Account::_displayTimestamp();
	std::cout << " "
			  << "index:" << this->_accountIndex << DELIM
			  << "p_amount:" << p_amount << DELIM
			  << "withdrawal:";
	if (withdrawal <= this->_amount) {
		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		Account::_totalAmount -= withdrawal;
		Account::_totalNbWithdrawals++;
		std::cout << withdrawal << DELIM << "amount:" << this->_amount << DELIM
				  << "nb_withdrawals:" << this->_nbWithdrawals << std::endl;
		return true;
	}
	else {
		std::cout << "refused" << std::endl;
		return false;
	}
}

int Account::checkAmount(void) const
{
	return this->_amount;
}

void Account::displayStatus(void) const
{
	Account::_displayTimestamp();
	std::cout << " "
			  << "index:" << this->_accountIndex << DELIM
			  << "amount:" << this->_amount << DELIM
			  << "deposits:" << this->_nbDeposits << DELIM
			  << "withdrawals:" << this->_nbWithdrawals << std::endl;
}

void Account::_displayTimestamp(void)
{
	time_t timestamp = time(NULL);
	struct tm* datetime = localtime(&timestamp);
	if (!datetime) {
		return;
	}

	char output[18];
	strftime(output, 18, "[%Y%m%d_%H%M%S]", datetime);
	std::cout << output;
}
