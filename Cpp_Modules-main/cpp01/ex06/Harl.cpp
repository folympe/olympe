
#include "Harl.hpp"
#include <iostream>

Harl::Harl (void)
{
	return ;
}

Harl::~Harl (void)
{
	return ;
}

void	Harl::_debug( void )
{
	std::cout << "[ DEBUG ]" << std::endl
		<< "I love having extra bacon for my "
		"7XL-double-cheese-triple-pickle-specialketchup burger. "
		"I really do!"
		<< std::endl << std::endl;
	return ;
}

void	Harl::_info( void )
{
	std::cout << "[ INFO ]" << std::endl
		<< "I cannot believe adding extra bacon costs more money. "
		"You didn't put enough bacon in my burger! If you did, "
		"I wouldn't be asking for more!"
		<< std::endl << std::endl;
	return ;
}

void	Harl::_warning( void )
{
	std::cout << "[ WARNING ]" << std::endl
		<< "I think I deserve to have some extra bacon for free. "
		"I've been coming for years whereas you started working here "
		"since last month."
		<< std::endl << std::endl;
	return ;
}

void	Harl::_error( void )
{
	std::cout << "[ ERROR ]" << std::endl
		<< "This is unacceptable! I want to speak to the manager now."
		<< std::endl << std::endl;
	return ;
}

void	Harl::complain(std::string level)
{
	typedef void (Harl::*t_function)(void);

	const std::string	levels[] = {
		"DEBUG", "INFO", "WARNING", "ERROR"
	};
	t_function	actions[] = {
		&Harl::_debug, &Harl::_info,
		&Harl::_warning, &Harl::_error
	};
	int	i = 0;

	while (i < 4)
	{
		if (level == levels[i])
		{
			(this->*actions[i])();
			return ;
		}
		i++;
	}
	std::cout << "Son of a member function pointer! There is no level \""
		<< level << "\"." << std::endl;
}
