
#include <string>
#include <iostream>

int	main(void)
{
	const std::string	message("HI THIS IS BRAIN");
	const std::string	*ptr = &message;
	const std::string	&ref = message;

	std::cout << "---- Memory addresses:\n";
	std::cout << "Address of string:\t\t" << &message << "\n";
	std::cout << "Address held by stringPTR:\t" << ptr << "\n";
	std::cout << "Address held by stringREF:\t" << &ref << std::endl;

	std::cout << "\n---- Values:\n";
	std::cout << "Value of string:\t\t[" << message << "]\n";
	std::cout << "Value pointed to by stringPTR:\t[" << *ptr << "]\n";
	std::cout << "Value pointed to by stringREF:\t[" << ref << "]" << std::endl;

	return (0);
}