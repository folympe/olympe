
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