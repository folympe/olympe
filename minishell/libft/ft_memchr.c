/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:16:24 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 11:16:26 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				cur;
	unsigned char const	*data;

	cur = 0;
	data = (unsigned char const *)s;
	while (cur < n)
	{
		if (data[cur] == (unsigned char)c)
			return ((void *)(data + cur));
		cur++;
	}
	return (NULL);
}
