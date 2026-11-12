/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 15:00:25 by olfhal            #+#    #+#             */
/*   Updated: 2026/10/23 15:00:27 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <iostream>
#include "Account.hpp"
#include <sstream>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

/*	Default	constructor	*/
Account::Account(void) : _accountIndex(_nbAccounts),
						_amount(0),
						_nbDeposits(0),
						_nbWithdrawals(0) {
	Account::_nbAccounts++;
	return ;
}

/*	Constructor	*/
Account::Account(int initial_deposit)
	: _accountIndex(_nbAccounts),
	  _amount(initial_deposit),
	  _nbDeposits(0),
	  _nbWithdrawals(0)
{
	++_nbAccounts;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << _amount << ";"
			  << "created" << std::endl;
}

/*	Destructor	*/
Account::~Account(void)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";"
			  << "amount:" << _amount << ";"
			  << "closed" << std::endl;
	--_nbAccounts;
}

/*	Returns the number of accounts	*/
int	Account::getNbAccounts( void ) {
	return (Account::_nbAccounts);
}

/*	Returns the total amount in all accounts	*/
int	Account::getTotalAmount( void ) {
	return (Account::_totalAmount);
}

/*	Returns the total number of deposits	*/
int	Account::getNbDeposits( void ) {
	return (Account::_totalNbDeposits);
}

/*	Returns the total number of withdrawals	*/
int	Account::getNbWithdrawals( void ) {
	return (Account::_totalNbWithdrawals);
}

void	Account::_displayTimestamp(void)
{
	std::time_t	current;
	struct tm	*date;

	current = std::time(NULL);
	date = std::localtime(&current);
	if (!date)
		return ;
	std::cout << "[";
	std::cout << date->tm_year + 1900;
	std::cout << (date->tm_mon < 10 ? "0" : "") << date->tm_mon;
	std::cout << (date->tm_mday < 10 ? "0" : "") << date->tm_mday;
	std::cout << "_";
	std::cout << (date->tm_hour < 10 ? "0" : "") << date->tm_hour;
	std::cout << (date->tm_min < 10 ? "0" : "") << date->tm_min;
	std::cout << (date->tm_sec < 10 ? "0" : "") << date->tm_sec;
	std::cout << "] ";
}

void	Account::makeDeposit(int deposit)
{
	int	oldAmount;

	oldAmount = _amount;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << oldAmount
			  << ";deposit:" << deposit;
	_amount = oldAmount + deposit;
	_nbDeposits += 1;
	_totalAmount += deposit;
	_totalNbDeposits += 1;
	std::cout << ";amount:" << _amount
			  << ";nb_deposits:" << _nbDeposits
			  << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << _amount
			  << ";withdrawal:";

	if (withdrawal <= _amount)
	{
		_amount -= withdrawal;
		_totalAmount -= withdrawal;
		++_nbWithdrawals;
		++_totalNbWithdrawals;
		std::cout << withdrawal
				  << ";amount:" << _amount
				  << ";nb_withdrawals:" << _nbWithdrawals
				  << std::endl;
		return (true);
	}
	std::cout << "refused" << std::endl;
	return (false);
}

int		Account::checkAmount( void ) const {
	return (this->_amount);
}

void	Account::displayStatus(void) const
{
	std::ostringstream	info;

	info << "index:" << _accountIndex << ";";
	info << "amount:" << _amount << ";";
	info << "deposits:" << _nbDeposits << ";";
	info << "withdrawals:" << _nbWithdrawals;

	_displayTimestamp();
	std::cout << info.str() << std::endl;
}

void	Account::displayAccountsInfos(void)
{
	int	accounts;
	int	total;
	int	deposits;
	int	withdrawals;

	accounts = getNbAccounts();
	total = getTotalAmount();
	deposits = getNbDeposits();
	withdrawals = getNbWithdrawals();

	_displayTimestamp();
	std::cout << "accounts:" << accounts
			  << ";total:" << total
			  << ";deposits:" << deposits
			  << ";withdrawals:" << withdrawals
			  << std::endl;
}