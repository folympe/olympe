
#ifndef HUMAN_B_CLASS_H
# define HUMAN_B_CLASS_H

# include <string>
# include "Weapon.hpp"

class	HumanB
{
	private:
		Weapon				*_weapon;
		std::string const	_name;

	public:
		HumanB( std::string const aName );
		~HumanB( void );
		void	attack( void ) const;
		void	setWeapon( Weapon &aWeapon );
};

#endif