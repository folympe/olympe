
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>
#include <string>

int main(void)
{
    std::string fragTrapName = "FT-356";
    std::string scavTrapName = "SCVT-2000";
    std::string clapTrapName = "CT-42";

    FragTrap fragTrap(fragTrapName);
    ScavTrap scavTrap(scavTrapName);
    ClapTrap clapTrap(clapTrapName);

    fragTrap.highFivesGuys();

    clapTrap.attack(scavTrapName);
    scavTrap.takeDamage(CLAPTRAP_DEFAULT_ATTACK_DAMAGE);

    scavTrap.attack(fragTrapName);
    fragTrap.takeDamage(SCAVTRAP_DEFAULT_ATTACK_DAMAGE);
    fragTrap.beRepaired(5);

    scavTrap.guardGate();

    for (int i = 0; i < 100; i++)
    {
        fragTrap.attack(scavTrapName);
        scavTrap.takeDamage(FRAGTRAP_DEFAULT_ATTACK_DAMAGE);
    }

    scavTrap.beRepaired(20);

    fragTrap.highFivesGuys();
    fragTrap.takeDamage(5000);
    fragTrap.highFivesGuys();

    return (0);
}
