/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:21:06 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 11:21:08 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		cur;
	char	*ret;

	cur = 0;
	ret = 0;
	while (s[cur])
	{
		if (s[cur] == (unsigned char)c)
			ret = (char *)(s + cur);
		cur++;
	}
	if (s[cur] == (unsigned char)c)
		ret = (char *)(s + cur);
	return (ret);
}
