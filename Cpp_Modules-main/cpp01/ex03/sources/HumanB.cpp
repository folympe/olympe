
#include <string>
#include <iostream>
#include "HumanB.hpp"

HumanB::HumanB(const std::string aName)
	: _name(aName), _weapon(NULL)
{
	std::cout << _name
			  << " enters the Colosseum with a whimper."
			  << std::endl;
}

HumanB::~HumanB(void)
{
	std::cout << _name
			  << " flees the Colosseum!"
			  << std::endl;
}

void	HumanB::setWeapon(Weapon &aWeapon)
{
	bool	hadWeapon = (_weapon && !_weapon->getType().empty());
	bool	hasNewWeapon = !aWeapon.getType().empty();

	if (!hasNewWeapon)
	{
		if (hadWeapon)
			std::cout << _name << " drops their weapon!" << std::endl;
		else
			std::cout << _name
					  << " tries to pick up a weapon but fails!"
					  << std::endl;
	}
	else
	{
		if (hadWeapon)
			std::cout << _name << " switches to a "
					  << aWeapon.getType() << std::endl;
		else
			std::cout << _name << " picks up a "
					  << aWeapon.getType() << std::endl;
	}
	if (hasNewWeapon)
		_weapon = &aWeapon;
	else
		_weapon = NULL;
}

void	HumanB::attack(void) const
{
	std::string	weaponName;

	std::cout << _name << " attacks with their ";
	if (_weapon)
		weaponName = _weapon->getType();
	if (weaponName.empty())
		std::cout << "bare fists!";
	else
		std::cout << weaponName << ".";
	std::cout << std::endl;
}
