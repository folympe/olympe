/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:13:28 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:13:30 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_CLASS_H
# define WEAPON_CLASS_H

# include <string>

class Weapon
{
	public:
		Weapon(const std::string type);
		~Weapon(void);

		void setType(const std::string newType);
		const std::string &getType(void) const;

	private:
		std::string _type;
};

#endif
