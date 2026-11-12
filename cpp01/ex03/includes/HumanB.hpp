/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:12:59 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:13:01 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
