
#include <string>
#include <iostream>
#include "HumanA.hpp"

HumanA::HumanA(const std::string aName, const Weapon &aWeapon)
	: _weapon(aWeapon), _name(aName)
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
