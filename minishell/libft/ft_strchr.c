/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:18:47 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 11:18:50 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

char	*ft_strchr(const char *str, int c)
{
	char	cpy;
	int		i;

	i = 0;
	cpy = (unsigned char)c;
	if (cpy == '\0')
	{
		while (str[i])
			i++;
		return ((char *)str + i);
	}
	while (str[i])
	{
		if (str[i] == cpy)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
