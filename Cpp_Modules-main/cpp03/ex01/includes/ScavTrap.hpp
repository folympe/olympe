
#ifndef SCAVTRAP_CLASS_H
# define SCAVTRAP_CLASS_H

# include "ClapTrap.hpp"

# define SCAVTRAP_DEFAULT_HIT_POINTS 100
# define SCAVTRAP_DEFAULT_ENERGY_POINTS 50
# define SCAVTRAP_DEFAULT_ATTACK_DAMAGE 20

class ScavTrap : public ClapTrap
{
	public:
		ScavTrap(const std::string& name);
		ScavTrap(const ScavTrap& src);
		~ScavTrap(void);

		ScavTrap& operator=(const ScavTrap& src);

		void attack(std::string& target);
		void guardGate(void);

	private:
		ScavTrap(void);
};

#endif