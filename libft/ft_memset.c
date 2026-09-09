/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:25:29 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 11:25:31 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	cur;
	char	*data;

	cur = 0;
	data = (char *)s;
	while (cur < n)
	{
		data[cur] = c;
		cur++;
	}
	return (s);
}
