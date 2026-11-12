/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 13:54:10 by olfhal            #+#    #+#             */
/*   Updated: 2026/11/12 13:54:13 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main( void )
{
	Harl	grumblerHarl;

	grumblerHarl.complain("DEBUG");
	grumblerHarl.complain("ERROR");
	grumblerHarl.complain("INFO");
	grumblerHarl.complain("WARNING");
	grumblerHarl.complain("BAD_JOKES");
	return ( 0 );
}
