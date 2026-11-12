/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:47:23 by olfhal            #+#    #+#             */
/*   Updated: 2026/10/23 14:47:24 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Contact.class.hpp"

/*	Constructor	*/
Contact::Contact(void) : _firstname(""),
						 _lastname(""),
						 _nickname(""),
						 _number(""),
						 _secret("")
{
	return;
}

/*	Desctructor	*/
Contact::~Contact(void)
{
	return;
}

/*	Returns the firstname private variable	*/
std::string const Contact::getFirstname(void) const
{
	return (this->_firstname);
}

/*	Returns the lastname private variable	*/
std::string const Contact::getLastname(void) const
{
	return (this->_lastname);
}

/*	Returns the nickname private variable	*/
std::string const Contact::getNickname(void) const
{
	return (this->_nickname);
}

/*	Returns the phone number private variable	*/
std::string const Contact::getNumber(void) const
{
	return (this->_number);
}

/*	Returns the darkest secret private variable	*/
std::string const Contact::getSecret(void) const
{
	return (this->_secret);
}

bool Contact::setFirstname(std::string str)
{
	if (!_containsOnlyAlpha(str))
	{
		if (!str.empty())
			std::cout << "Error: Names can only contain letters, spaces "
					  << "and hyphens." << std::endl;
		return (false);
	}

	str.at(0) = std::toupper(static_cast<unsigned char>(str.at(0)));
	_firstname.assign(str);
	return (true);
}

bool Contact::setLastname(std::string str)
{
	if (str.empty() || !_containsOnlyAlpha(str))
	{
		if (!str.empty())
			std::cout << "Error: Names can only contain letters, "
					  << "spaces and hyphens." << std::endl;
		return (false);
	}

	std::string::size_type pos = 0;
	while (pos < str.size())
	{
		str[pos] = std::toupper(
			static_cast<unsigned char>(str[pos]));
		++pos;
	}
	_lastname = str;
	return (true);
}

bool Contact::setNickname(std::string str)
{
	if (str.empty() || !_containsOnlyAlpha(str))
	{
		if (!str.empty())
			std::cout << "Error: Names can only contain letters, "
					  << "spaces and hyphens." << std::endl;
		return (false);
	}

	str[0] = std::toupper(static_cast<unsigned char>(str[0]));
	_nickname.swap(str);
	return (true);
}

bool Contact::setNumber(std::string const str)
{
	if (str.empty() || !_containsOnlyDigits(str))
	{
		if (!str.empty())
			std::cout << "Error: Phone numbers can only contain digits, "
					  << "spaces and hyphens." << std::endl;
		return (false);
	}

	_number.assign(str);
	return (true);
}

bool Contact::setSecret(std::string const str)
{
	if (!str.size())
		return (false);

	_secret.assign(str);
	return (true);
}

bool Contact::_containsOnlyAlpha(std::string const s)
{
	std::string::size_type i = 0;

	while (i < s.length())
	{
		unsigned char c = s[i];

		if (!std::isalpha(c) && c != ' ' && c != '-')
			return (false);
		++i;
	}
	return (true);
}

bool	Contact::_containsOnlyDigits(std::string const s)
{
	for (std::string::const_iterator pos = s.begin();
			pos != s.end(); ++pos)
	{
		if (*pos == ' ' || *pos == '-')
			continue ;
		if (!std::isdigit(static_cast<unsigned char>(*pos)))
			return (false);
	}
	return (true);
}

bool	Contact::isEmpty(void) const
{
	return (_firstname.empty()
		|| _lastname.empty()
		|| _nickname.empty()
		|| _number.empty()
		|| _secret.empty());
}

bool	Contact::displayContactInfo(void) const
{
	if (isEmpty())
		return (false);

	std::cout << "+ First name\t: " << getFirstname() << '\n';
	std::cout << "+ Last name\t: " << getLastname() << '\n';
	std::cout << "+ Nickname\t: " << getNickname() << '\n';
	std::cout << "+ Phone number\t: " << getNumber() << '\n';
	std::cout << "+ Darkest secret: " << getSecret() << '\n';

	return (true);
}
