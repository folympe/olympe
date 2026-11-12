
#ifndef FRAGTRAP_CLASS_H
# define FRAGTRAP_CLASS_H

#include "ClapTrap.hpp"

# define FRAGTRAP_DEFAULT_HIT_POINTS 100
# define FRAGTRAP_DEFAULT_ENERGY_POINTS 100
# define FRAGTRAP_DEFAULT_ATTACK_DAMAGE 30

class FragTrap : public ClapTrap
{
	public:
		FragTrap(std::string & name);
		FragTrap(FragTrap const & src);
		~FragTrap(void);

		FragTrap &	operator=(FragTrap const & src);

		void	highFivesGuys(void);

	private:
		FragTrap(void);
};

#endif