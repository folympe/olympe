/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 14:42:53 by olfhal            #+#    #+#             */
/*   Updated: 2026/10/23 14:42:56 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int argc, char **argv)
{
	std::string	output;

	if (argc < 2)
		output = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			std::string	word = argv[i];
			for (std::string::size_type j = 0; j < word.length(); ++j)
				word[j] = std::toupper(
					static_cast<unsigned char>(word[j]));
			output += word;
		}
	}
	std::cout << output << '\n';
	return (0);
}
