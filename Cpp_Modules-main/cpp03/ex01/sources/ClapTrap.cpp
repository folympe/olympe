
#include "ClapTrap.hpp"
#include "Colors.h"
#include <iostream>
#include <string>

ClapTrap::ClapTrap(void)
	: _name("Default"),
	  _hitPoints(CLAPTRAP_DEFAULT_HIT_POINTS),
	  _energyPoints(CLAPTRAP_DEFAULT_ENERGY_POINTS),
	  _attackDamage(CLAPTRAP_DEFAULT_ATTACK_DAMAGE),
	  _maxHitPoints(CLAPTRAP_DEFAULT_HIT_POINTS),
	  _maxEnergyPoints(CLAPTRAP_DEFAULT_ENERGY_POINTS),
	  _maxAttackDamage(CLAPTRAP_DEFAULT_ATTACK_DAMAGE)
{
	std::cerr << CYAN
		<< "ClapTrap default constructor called."
		<< RESET << std::endl;
}

ClapTrap::ClapTrap(std::string name)
    : _name(name),
      _hitPoints(CLAPTRAP_DEFAULT_HIT_POINTS),
      _energyPoints(CLAPTRAP_DEFAULT_ENERGY_POINTS),
      _attackDamage(CLAPTRAP_DEFAULT_ATTACK_DAMAGE),
      _maxHitPoints(CLAPTRAP_DEFAULT_HIT_POINTS),
      _maxEnergyPoints(CLAPTRAP_DEFAULT_ENERGY_POINTS),
      _maxAttackDamage(CLAPTRAP_DEFAULT_ATTACK_DAMAGE)
{
    std::cerr << CYAN "A ClapTrap named \"" << name
              << "\" was constructed." RESET << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const & src)
{
    std::cerr << CYAN "ClapTrap copy constructor called." RESET << std::endl;
    *this = src;
}

ClapTrap::~ClapTrap(void)
{
    std::cerr << CYAN "The ClapTrap named \"" << _name
              << "\" was destroyed." RESET << std::endl;
}

ClapTrap & ClapTrap::operator=(ClapTrap const & src)
{
    if (this != &src)
    {
        _name = src.getName();
        _hitPoints = src.getHitPoints();
        _energyPoints = src.getEnergyPoints();
        _attackDamage = src.getAttackDamage();
    }
    return (*this);
}

std::string	ClapTrap::getName(void) const {
	return (this->_name);
}

unsigned int	ClapTrap::getHitPoints(void) const {
	return (this->_hitPoints);
}

unsigned int	ClapTrap::getEnergyPoints(void) const {
	return (this->_energyPoints);
}

unsigned int	ClapTrap::getAttackDamage(void) const {
	return (this->_attackDamage);
}

void    ClapTrap::attack(std::string & target)
{
    if (_hitPoints == 0)
    {
        std::cout << YELLOW "ClapTrap " << _name
                  << " can't attack: it is destroyed."
                  << RESET << std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout << YELLOW "ClapTrap " << _name
                  << " can't attack: its battery is depleted."
                  << RESET << std::endl;
        return ;
    }
    if (target == _name)
        target = "itself";
    _energyPoints--;
    std::cout << YELLOW "ClapTrap " << _name
              << " attacks " << target
              << " and hits for " << _attackDamage
              << " damage!" RESET << std::endl;
}

void    ClapTrap::takeDamage(unsigned int amount)
{
    if (_hitPoints == 0)
    {
        std::cout << RED << _name
                  << " can't take anymore damage: it is already beyond repair!"
                  << RESET << std::endl;
        return ;
    }
    if (amount >= _hitPoints)
    {
        _hitPoints = 0;
        std::cout << RED << _name
                  << " takes " << amount
                  << " damage and is destroyed!"
                  << RESET << std::endl;
    }
    else
    {
        _hitPoints -= amount;
        std::cout << RED << _name
                  << " takes " << amount
                  << " damage!" << RESET << std::endl;
    }
}

void    ClapTrap::beRepaired(unsigned int amount)
{
    if (_hitPoints == 0)
    {
        std::cout << GREEN << _name
                  << " can't repair itself: it is too severely damaged."
                  << RESET << std::endl;
        return ;
    }
    if (_energyPoints == 0)
    {
        std::cout << GREEN << _name
                  << " can't repair itself: its battery is depleted and needs recharging."
                  << RESET << std::endl;
        return ;
    }
    if ((_hitPoints + amount) > _maxHitPoints)
        amount = _maxHitPoints - _hitPoints;
    if (amount == 0)
    {
        _energyPoints--;
        std::cout << GREEN << _name
                  << " wastes energy trying to repair itself when it is already in tip top shape."
                  << RESET << std::endl;
        return ;
    }
    _energyPoints--;
    _hitPoints += amount;
    std::cout << GREEN << _name << " repairs itself for "
              << amount << "." RESET << std::endl;
}
