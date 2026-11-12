
#ifndef HARL_H
# define HARL_H

# include <string>

class Harl
{
	public:
		Harl(void);
		~Harl(void);

		void complain(std::string level);

	private:
		void _debug(void);
		void _info(void);
		void _warning(void);
		void _error(void);
};

#endif