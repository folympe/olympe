
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