
#include "Colors.h"
#include "ScavTrap.hpp"
#include <iostream>
#include <string>

ScavTrap::ScavTrap(void) : ClapTrap()
{
    std::cout << CYAN "ScavTrap default constructor called."
              << RESET << std::endl;
    _hitPoints = SCAVTRAP_DEFAULT_HIT_POINTS;
    _maxHitPoints = SCAVTRAP_DEFAULT_HIT_POINTS;
    _energyPoints = SCAVTRAP_DEFAULT_ENERGY_POINTS;
    _maxEnergyPoints = SCAVTRAP_DEFAULT_ENERGY_POINTS;
    _attackDamage = SCAVTRAP_DEFAULT_ATTACK_DAMAGE;
    _maxAttackDamage = SCAVTRAP_DEFAULT_ATTACK_DAMAGE;
}

ScavTrap::ScavTrap(std::string & name) : ClapTrap(name)
{
    std::cout << CYAN "A ScavTrap named \"" << name
              << "\" was constructed." RESET << std::endl;
    _hitPoints = SCAVTRAP_DEFAULT_HIT_POINTS;
    _maxHitPoints = SCAVTRAP_DEFAULT_HIT_POINTS;
    _energyPoints = SCAVTRAP_DEFAULT_ENERGY_POINTS;
    _maxEnergyPoints = SCAVTRAP_DEFAULT_ENERGY_POINTS;
    _attackDamage = SCAVTRAP_DEFAULT_ATTACK_DAMAGE;
    _maxAttackDamage = SCAVTRAP_DEFAULT_ATTACK_DAMAGE;
}

ScavTrap::ScavTrap(ScavTrap const & src) : ClapTrap(src)
{
    std::cout << CYAN "ScavTrap copy constructor called."
              << RESET << std::endl;
}

ScavTrap::~ScavTrap(void)
{
    std::cout << CYAN "The ScavTrap named \"" << _name
              << "\" was destroyed." RESET << std::endl;
}

ScavTrap & ScavTrap::operator=(ScavTrap const & src)
{
    if (this != &src)
    {
        ClapTrap::operator=(src);
    }
    return (*this);
}

void    ScavTrap::attack(std::string & target)
{
    if (_hitPoints == 0)
    {
        std::cout << YELLOW "ScavTrap " << _name
                  << " can't attack: it is destroyed."
                  << RESET << std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout << YELLOW "ScavTrap " << _name
                  << " can't attack: its battery is depleted."
                  << RESET << std::endl;
        return ;
    }
    if (target == _name)
        target = "itself";
    _energyPoints--;
    std::cout << YELLOW "ScavTrap " << _name
              << " leaps on " << target
              << " and crushes it for " << _attackDamage
              << " damage!" RESET << std::endl;
}

void    ScavTrap::guardGate(void)
{
    if (_hitPoints == 0)
    {
        std::cout << PURPLE << _name
                  << " can't guard the gate in its broken state."
                  << RESET << std::endl;
    }
    else
    {
        std::cout << PURPLE << _name
                  << " switches to Gate guarding mode."
                  << RESET << std::endl;
    }
}
