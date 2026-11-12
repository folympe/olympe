
#include "Colors.h"
#include "FragTrap.hpp"
#include <iostream>
#include <string>

FragTrap::FragTrap(void) : ClapTrap()
{
    std::cout << CYAN "FragTrap default constructor called."
              << RESET << std::endl;

    _hitPoints = FRAGTRAP_DEFAULT_HIT_POINTS;
    _maxHitPoints = FRAGTRAP_DEFAULT_HIT_POINTS;

    _energyPoints = FRAGTRAP_DEFAULT_ENERGY_POINTS;
    _maxEnergyPoints = FRAGTRAP_DEFAULT_ENERGY_POINTS;

    _attackDamage = FRAGTRAP_DEFAULT_ATTACK_DAMAGE;
    _maxAttackDamage = FRAGTRAP_DEFAULT_ATTACK_DAMAGE;
}

FragTrap::FragTrap(std::string & name) : ClapTrap(name)
{
    std::cout << CYAN "A FragTrap named \"" << name
              << "\" was constructed." RESET << std::endl;

    _hitPoints = FRAGTRAP_DEFAULT_HIT_POINTS;
    _maxHitPoints = FRAGTRAP_DEFAULT_HIT_POINTS;

    _energyPoints = FRAGTRAP_DEFAULT_ENERGY_POINTS;
    _maxEnergyPoints = FRAGTRAP_DEFAULT_ENERGY_POINTS;

    _attackDamage = FRAGTRAP_DEFAULT_ATTACK_DAMAGE;
    _maxAttackDamage = FRAGTRAP_DEFAULT_ATTACK_DAMAGE;
}

FragTrap::FragTrap(FragTrap const & src) : ClapTrap(src)
{
    std::cout << CYAN "FragTrap copy constructor called."
              << RESET << std::endl;
}

FragTrap::~FragTrap(void)
{
    std::cout << CYAN "The FragTrap named \"" << _name
              << "\" was destroyed." RESET << std::endl;
}

FragTrap & FragTrap::operator=(FragTrap const & src)
{
    if (this != &src)
    {
        ClapTrap::operator=(src);
    }
    return (*this);
}

void    FragTrap::highFivesGuys(void)
{
    if (_hitPoints == 0)
    {
        std::cout << PURPLE << _name
                  << " extends a fingerless hand from its debris for a high-five."
                  << RESET << std::endl;
    }
    else
    {
        std::cout << PURPLE << _name
                  << " jumps around trying to get "
                  "someone to high-five it."
                  << RESET << std::endl;
    }
}
