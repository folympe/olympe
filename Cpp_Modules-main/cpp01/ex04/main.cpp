
#include <errno.h>
#include <string.h>
#include <iostream>
#include <fstream>

void	printUsage(const char *name)
{
	std::cout << "Usage: " << name
			  << " <filename> <string_to_replace>"
			  << " <replacement_string>\n";
}

int	openSteams(std::ifstream *ifs, std::ofstream *ofs,
				std::string infile, std::string outfile)
{
	ifs->open(infile.c_str(), std::ios::in);
	if (!ifs->is_open() || !ifs->good())
	{
		std::cerr << "Error: " << infile << ": "
				  << strerror(errno) << std::endl;
		return (-1);
	}

	ofs->open(outfile.c_str(), std::ios::out | std::ios::trunc);
	if (!ofs->is_open() || !ofs->good())
	{
		ifs->close();
		std::cerr << "Error: " << outfile << ": "
				  << strerror(errno) << std::endl;
		return (-1);
	}
	return (0);
}

void	replaceBuffer(std::string *buffer, const std::string target,
					const std::string subst)
{
	std::string::size_type	pos = 0;

	if (target.empty())
		return ;

	while ((pos = buffer->find(target, pos)) != std::string::npos)
	{
		buffer->replace(pos, target.length(), subst);
		pos += subst.length();
	}
}

int	copyContents(std::ifstream *ifs, std::ofstream *ofs,
				const std::string target, const std::string subst)
{
	std::string	line;

	while (std::getline(*ifs, line))
	{
		replaceBuffer(&line, target, subst);
		*ofs << line;

		if (!ifs->eof())
			*ofs << '\n';

		if (!ofs->good())
			return (-1);
	}
	if (ifs->bad())
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	std::ifstream	ifs;
	std::ofstream	ofs;
	std::string		infile;
	std::string		outfile;

	if (ac != 4)
	{
		printUsage(av[0]);
		return (1);
	}

	infile = av[1];
	outfile = infile + ".replace";

	if (openSteams(&ifs, &ofs, infile, outfile) != 0)
		return (1);

	if (copyContents(&ifs, &ofs, av[2], av[3]) != 0)
	{
		ifs.close();
		ofs.close();
		return (1);
	}

	ifs.close();
	ofs.close();
	return (0);
}