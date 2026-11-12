
#include "ClapTrap.hpp"
#include "Colors.h"
#include <iostream>
#include <string>

ClapTrap::ClapTrap(void)
	: _name("Default"),
	  _hitPoints(ClapTrap::defaultHitPoints),
	  _energyPoints(ClapTrap::defaultEnergyPoints),
	  _attackDamage(ClapTrap::defaultAttackDamage)
{
	std::cerr << CYAN
		<< "ClapTrap default constructor called."
		<< RESET << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
	: _name(name),
	  _hitPoints(ClapTrap::defaultHitPoints),
	  _energyPoints(ClapTrap::defaultEnergyPoints),
	  _attackDamage(ClapTrap::defaultAttackDamage)
{
	std::cerr << CYAN
		<< "A ClapTrap named \"" << name
		<< "\" was constructed."
		<< RESET << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& src)
	: _name(src._name),
	  _hitPoints(src._hitPoints),
	  _energyPoints(src._energyPoints),
	  _attackDamage(src._attackDamage)
{
	std::cerr << CYAN
		<< "ClapTrap copy constructor called."
		<< RESET << std::endl;
}

ClapTrap::~ClapTrap(void)
{
	std::cerr << CYAN
		<< "The ClapTrap named \"" << _name
		<< "\" was destroyed."
		<< RESET << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& src)
{
	if (this != &src)
	{
		_name = src._name;
		_hitPoints = src._hitPoints;
		_energyPoints = src._energyPoints;
		_attackDamage = src._attackDamage;
	}
	return (*this);
}

std::string ClapTrap::getName(void) const
{
	return (_name);
}

unsigned int ClapTrap::getHitPoints(void) const
{
	return (_hitPoints);
}

unsigned int ClapTrap::getEnergyPoints(void) const
{
	return (_energyPoints);
}

unsigned int ClapTrap::getAttackDamage(void) const
{
	return (_attackDamage);
}

void ClapTrap::attack(std::string& target)
{
	if (_hitPoints == 0)
	{
		std::cout << YELLOW
			<< "ClapTrap " << _name
			<< " can't attack: it is destroyed."
			<< RESET << std::endl;
		return ;
	}
	if (_energyPoints == 0)
	{
		std::cout << YELLOW
			<< "ClapTrap " << _name
			<< " can't attack: its battery is depleted."
			<< RESET << std::endl;
		return ;
	}
	if (target == _name)
		target = "itself";
	_energyPoints--;
	std::cout << YELLOW
		<< "ClapTrap " << _name
		<< " attacks " << target
		<< " and hits for " << _attackDamage
		<< " damage!"
		<< RESET << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << RED
			<< "ClapTrap " << _name
			<< " can't take anymore damage: it is already beyond repair!"
			<< RESET << std::endl;
		return ;
	}
	if (amount >= _hitPoints)
	{
		_hitPoints = 0;
		std::cout << RED
			<< "ClapTrap " << _name
			<< " takes " << amount
			<< " damage and is destroyed!"
			<< RESET << std::endl;
	}
	else
	{
		_hitPoints -= amount;
		std::cout << RED
			<< "ClapTrap " << _name
			<< " takes " << amount
			<< " damage!"
			<< RESET << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << GREEN
			<< "ClapTrap " << _name
			<< " can't repair itself: it is too severely damaged."
			<< RESET << std::endl;
		return ;
	}
	if (_energyPoints == 0)
	{
		std::cout << GREEN
			<< "ClapTrap " << _name
			<< " can't repair itself: its battery is depleted and needs recharging."
			<< RESET << std::endl;
		return ;
	}
	if (amount > (defaultHitPoints - _hitPoints))
		amount = defaultHitPoints - _hitPoints;
	if (amount == 0)
	{
		_energyPoints--;
		std::cout << GREEN
			<< "ClapTrap " << _name
			<< " wastes energy trying to repair itself when it is already in tip top shape."
			<< RESET << std::endl;
		return ;
	}
	_energyPoints--;
	_hitPoints += amount;
	std::cout << GREEN
		<< "ClapTrap " << _name
		<< " repairs itself for " << amount << "."
		<< RESET << std::endl;
}
