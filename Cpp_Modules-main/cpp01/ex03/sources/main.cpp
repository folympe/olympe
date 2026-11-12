
#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"
#include <iostream>

int	main(void)
{
	Weapon	knife("butter knife");
	Weapon	club("crude spiked club");
	Weapon	flamethrower("flamethrower");
	Weapon	fists("");

	std::cout << "\n* WELCOME TO THE COLOSSEUM! *\n" << std::endl;

	HumanA	alice("Alice", club);
	HumanB	bob("Bob");

	std::cout << "\n* 3, 2, 1... FIGHT! *\n" << std::endl;

	alice.attack();
	bob.attack();

	bob.setWeapon(knife);
	club.setType("");
	alice.attack();
	bob.attack();

	bob.setWeapon(fists);
	club.setType("whip");
	alice.attack();
	bob.attack();

	bob.setWeapon(flamethrower);
	bob.attack();
	club.setType("butter knife");
	alice.attack();

	std::cout << std::endl;
	return (0);
}