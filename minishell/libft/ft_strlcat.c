/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:19:26 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 11:19:29 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	src_len;
	size_t	cur;

	src_len = ft_strlen(dest);
	cur = 0;
	if (n <= src_len)
		return (ft_strlen(src) + n);
	while (src[cur] && (src_len + cur) < (n - 1))
	{
		dest[src_len + cur] = src[cur];
		cur++;
	}
	dest[src_len + cur] = 0;
	return (ft_strlen(src) + src_len);
}
