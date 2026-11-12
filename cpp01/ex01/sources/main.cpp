/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:08:29 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:08:32 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <limits>
#include <string>
#include "Zombie.hpp"

#define LIMIT_MIN -50000
#define LIMIT_MAX 50000


Zombie *zombieHorde( int N, std::string name );

int	getNbZombies(void)
{
	int	count;

	std::cout << "Dear necromancer! How many zombies should we raise for our horde today?"
			  << std::endl << "> ";

	while (true)
	{
		if (std::cin >> count)
		{
			if (count >= LIMIT_MIN && count <= LIMIT_MAX)
				break ;
		}
		else if (std::cin.eof())
			return (0);

		std::cout << "Um... Let's be reasonable here. Why don't you try a number between "
				  << LIMIT_MIN << " and " << LIMIT_MAX << "?"
				  << std::endl << "> ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return (count);
}

std::string	getHordeName(void)
{
	std::string	hordeName;

	std::cin.ignore();
	std::cout << "Perfect! And what shall this horde be called?"
			  << std::endl << "> ";

	if (!std::getline(std::cin, hordeName))
		return ("");
	return (hordeName);
}

int	main(void)
{
	int			nb;
	std::string	name;
	Zombie		*horde;

	nb = getNbZombies();
	name = getHordeName();

	std::cout << "Attempting to raise the horde '" << name
			  << "', of " << nb << " zombies..." << std::endl;
	std::cout << "Allocating space for zombies..." << std::endl;
	horde = zombieHorde(nb, name);
	if (horde == NULL)
	{
		std::cout << "Your necromancy failed. These corpses will not rise."
				  << std::endl;
		return (1);
	}
	std::cout << "Mwahaha we have zombies...!" << std::endl;
	for (int i = 0; i < nb; ++i)
		horde[i].announce();

	std::cout << "Returning zombies to their graves..." << std::endl;
	delete[] horde;
	return (0);
}
