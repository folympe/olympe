/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:48:00 by olfhal            #+#    #+#             */
/*   Updated: 2026/10/23 14:48:04 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "PhoneBook.class.hpp"

std::string	getInput(PhoneBook *book)
{
	std::string	command;

	if (std::getline(std::cin, command))
	{
		command = book->trimBlank(command);
		for (std::string::size_type i = 0; i < command.size(); ++i)
			command[i] = std::toupper(
				static_cast<unsigned char>(command[i]));
		return (command);
	}

	std::cout << "EXIT" << std::endl;
	return ("EXIT");
}

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;

	std::cout << "\nWelcome to the 1981 Forget-Me-Not(TM) "
			  << "PhoneBook(c)!" << std::endl;

	while (true)
	{
		std::cout << "\n+---------------- Main Menu ----------------+\n"
				  << "\nWhat would you like to do?\n> ";

		command = getInput(&phoneBook);
		if (command == "EXIT")
			break ;

		if (command == "ADD" && !phoneBook.addContact())
			break ;
		else if (command == "SEARCH" && !phoneBook.searchContact())
			break ;
		else if (command != "ADD" && command != "SEARCH")
		{
			std::cout << "Please enter one of the following:\n"
					  << "\tADD\t: add a contact\n"
					  << "\tSEARCH\t: search contact list\n"
					  << "\tEXIT\t: exit the FMN(TM) PhoneBook(c)"
					  << std::endl;
		}
	}

	std::cout << "Thank you for using the Forget-Me-Not(TM) "
			  << "PhoneBook(c). Come again soon!" << std::endl;
	return (0);
}
