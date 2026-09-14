/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:17:46 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 11:17:49 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*data_dst;
	char	*data_src;

	if (!src && !dest)
		return (NULL);
	if (src > dest)
		dest = ft_memcpy(dest, src, len);
	else
	{
		data_dst = (char *)dest;
		data_src = (char *)src;
		while (len--)
			data_dst[len] = data_src[len];
	}
	return (dest);
}
