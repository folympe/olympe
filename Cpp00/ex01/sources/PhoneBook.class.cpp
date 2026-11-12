/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:49:09 by olfhal            #+#    #+#             */
/*   Updated: 2026/10/23 14:49:16 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iomanip>
#include <iostream>
#include <string>
#include "PhoneBook.class.hpp"

/*	Constructor	*/
PhoneBook::PhoneBook(void) : _index(-1), _abort(false) {
	return ;
}

/*	Destructor	*/
PhoneBook::~PhoneBook(void) {
	return ;
}

std::string	PhoneBook::_getInput(std::string const prompt)
{
	std::string	value;

	std::cout << "Please enter " << prompt << ":\n> ";

	if (std::getline(std::cin, value))
	{
		value = trimBlank(value);
		return (value);
	}

	_abort = true;
	std::cout << std::endl;
	return ("");
}

void	PhoneBook::_incrementIndex(void) {
	_index++;
	if (_index > 7) {
		_index = 0;
	}
}

void	PhoneBook::_displayContactTable(void) const
{
	const int	maxContacts = 8;

	std::cout << "+----------+----------+----------+----------+\n";
	std::cout << "|  INDEX   |FIRST NAME| LAST NAME| NICKNAME |\n";
	std::cout << "+----------+----------+----------+----------+\n";

	int	i = 0;
	while (i < maxContacts)
		_printContactInfoToTable(i++);
	std::cout << '\n';
}

void	PhoneBook::_printContactInfoToTable(int const index) const
{
	const Contact	&contact = _contactList[index];

	if (contact.isEmpty())
		return ;

	std::cout << "|" << std::setw(10) << index << "|";
	_printTableString(contact.getFirstname());
	_printTableString(contact.getLastname());
	_printTableString(contact.getNickname());

	std::cout << '\n'
			  << "+----------+----------+----------+----------+"
			  << '\n';
}

void	PhoneBook::_printTableString(std::string str) const
{
	const std::string::size_type	width = 10;

	if (str.size() >= width)
		str = str.substr(0, width - 1) + ".";

	std::cout << std::right << std::setw(width) << str << "|";
}

bool	PhoneBook::_displayContactByIndex(std::string const input) const
{
	int	index;

	if (input.size() != 1 || !std::isdigit(
			static_cast<unsigned char>(input[0])))
	{
		std::cout << "Error: '" << input
				  << "' is not a valid index (a digit between 0 and 7)."
				  << " Please try again later." << std::endl;
		return (false);
	}

	index = input[0] - '0';
	if (index > 7)
	{
		std::cout << "Error: '" << input
				  << "' is not a valid index (a digit between 0 and 7)."
				  << " Please try again later." << std::endl;
		return (false);
	}

	if (_contactList[index].displayContactInfo())
		return (true);

	std::cout << "Error: No record at index [" << index
			  << "]. Please ADD a contact and try again."
			  << std::endl;
	return (false);
}

std::string	PhoneBook::trimBlank(std::string str)
{
	const std::string blanks(" \t\n\r\v\f");
	std::string::size_type	first = str.find_first_not_of(blanks);

	if (first == std::string::npos)
		return ("");

	std::string::size_type	last = str.find_last_not_of(blanks);
	return (str.substr(first, last - first + 1));
}

bool	PhoneBook::addContact(void)
{
	std::string	input;

	_incrementIndex();
	std::cout << "\n+------------ New Contact Menu -------------+\n"
			  << std::endl;

	while (!_abort)
	{
		input = _getInput("a first name");
		if (_abort || _contactList[_index].setFirstname(input))
			break ;
	}
	while (!_abort)
	{
		input = _getInput("a last name");
		if (_abort || _contactList[_index].setLastname(input))
			break ;
	}
	while (!_abort)
	{
		input = _getInput("a nickname");
		if (_abort || _contactList[_index].setNickname(input))
			break ;
	}
	while (!_abort)
	{
		input = _getInput("a phone number");
		if (_abort || _contactList[_index].setNumber(input))
			break ;
	}
	while (!_abort)
	{
		input = _getInput("a darkest secret");
		if (_abort || _contactList[_index].setSecret(input))
			break ;
	}

	if (!_abort)
		std::cout << "Contact successfully saved." << std::endl;
	else
	{
		_abort = false;
		return (false);
	}
	return (true);
}

void	PhoneBook::displayContact(int index) const
{
	if (index < 0 || index > 7)
	{
		std::cout << "Error: No record for the requested contact."
				  << std::endl;
		return ;
	}

	if (!_contactList[index].displayContactInfo())
		std::cout << "Error: No record for the requested contact."
				  << std::endl;
}

bool	PhoneBook::searchContact(void)
{
	std::string	choice;

	std::cout << "\n+-------------- Search Menu ----------------+\n"
			  << std::endl;

	if (_index < 0)
	{
		std::cout << "No contacts in record. Please ADD a contact first."
				  << std::endl;
		return (true);
	}

	_displayContactTable();
	choice = _getInput("the index of the contact to display");

	if (choice.empty())
		return (false);

	return (_displayContactByIndex(choice));
}
