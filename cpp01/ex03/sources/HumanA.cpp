/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:14:29 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:14:31 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "HumanA.hpp"

HumanA::HumanA(const std::string aName, const Weapon &aWeapon)
    : _name(aName), _weapon(aWeapon)
{
    std::cout << _name
              << " enters the Colosseum with a roar!"
              << std::endl;
}

HumanA::~HumanA(void)
{
	std::cout << _name << " commits seppuku";
	if (!_weapon.getType().empty())
		std::cout << " with their " << _weapon.getType();
	std::cout << "." << std::endl;
}

void HumanA::attack(void) const
{
	std::cout << _name << " attacks with their ";
	const std::string &weaponType = _weapon.getType();
	if (weaponType.empty())
		std::cout << "bare hands!";
	else
		std::cout << weaponType << ".";
	std::cout << std::endl;
}
