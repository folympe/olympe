/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:08:57 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:08:58 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Zombie.hpp"

Zombie::Zombie( void )
{
	std::cout << "A zombie appeared!" << std::endl;
	return ;
}

Zombie::Zombie( std::string name ) : _name( name )
{
	std::cout << "A zombie named " << this->_getName() << " appeared!" << std::endl;
	return ;
}

Zombie::~Zombie( void )
{
	std::cout << this->_getName()
			<< ": nooo braiiiinz :((... deaaad agaiiiiiin...."
			<< std::endl;
	return ;
}

std::string Zombie::_getName( void ) const
{
	return (this->_name);
}

void	Zombie::setName( std::string const name )
{
	this->_name = name;
	return ;
}

void	Zombie::announce( void )
{
	std::cout << this->_getName() << ": BraiiiiiiinnnzzzZ..." << std::endl;
	return ;
}
