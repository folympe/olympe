
#ifndef CLAPTRAP_CLASS_H
# define CLAPTRAP_CLASS_H

# include <string>

# define CLAPTRAP_DEFAULT_HIT_POINTS 10
# define CLAPTRAP_DEFAULT_ENERGY_POINTS 10
# define CLAPTRAP_DEFAULT_ATTACK_DAMAGE 0

class ClapTrap
{
	public:
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap& src);
		~ClapTrap(void);

		ClapTrap& operator=(const ClapTrap& src);

		std::string		getName(void) const;
		unsigned int	getHitPoints(void) const;
		unsigned int	getEnergyPoints(void) const;
		unsigned int	getAttackDamage(void) const;

		void attack(std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

	protected:
		ClapTrap(void);

		std::string		_name;
		unsigned int	_hitPoints;
		unsigned int	_energyPoints;
		unsigned int	_attackDamage;
		unsigned int	_maxHitPoints;
		unsigned int	_maxEnergyPoints;
		unsigned int	_maxAttackDamage;
};

#endif
