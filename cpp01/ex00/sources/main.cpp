/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:59:48 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 12:59:51 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Zombie.hpp"

Zombie	*newZombie( std::string name );
void	randomChump( std::string name );


int	main(void)
{
	Zombie	*undead[3];

	undead[0] = newZombie("trista");
	undead[1] = newZombie("Greg");
	undead[2] = newZombie("lise");

	randomChump("ronflex");
	randomChump("cleo");
	randomChump("Chloe");

	for (int i = 0; i < 3; ++i)
	{
		undead[i]->announce();
		if (i != 1)
			delete undead[i];
	}
	delete undead[1];
	return (0);
}
