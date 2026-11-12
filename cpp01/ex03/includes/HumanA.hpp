/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:12:42 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:12:44 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A_CLASS_H
# define HUMAN_A_CLASS_H

# include <string>
# include "Weapon.hpp"

class HumanA
{
	public:
		HumanA(const std::string name, const Weapon &weapon);
		~HumanA(void);

		void attack(void) const;

	private:
		const std::string _name;
		const Weapon &_weapon;
};

#endif
